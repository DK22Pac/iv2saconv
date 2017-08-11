#pragma once
#include "formats\rage\BlockMap.h"
#include <stdio.h>
#include <vector>
#include "zlib.h"
#include "..\converter\source\Error.h"

inline rage::BlockMap* UnwrapRSC5(const char* fileName) {
    FILE* f = fopen(fileName, "rb");
    if (!f)
        return nullptr;
    fseek(f, 0, SEEK_END);
    size_t fileLength = ftell(f) - 12;
    fseek(f, 0, SEEK_SET);

    unsigned int magic;
    fread(&magic, 1, sizeof(magic), f);

    if (magic != 0x05435352) {
        printf("Invalid RSC file\n");
        fclose(f);
        return nullptr;
    }

    unsigned int version;
    fread(&version, 1, sizeof(version), f);

    if (version != 110 && version != 32 && version != 8) {
        printf("RSC version not supported\n");
        fclose(f);
        return nullptr;
    }

    unsigned int flags;
    fread(&flags, 1, sizeof(flags), f);

    unsigned int virtualSize = (flags & 0x7FF) << (((flags >> 11) & 0xF) + 8);
    unsigned int physicalSize = ((flags >> 15) & 0x7FF) << (((flags >> 26) & 0xF) + 8);

    unsigned char *tempBytes = new unsigned char[virtualSize + physicalSize];

    {
        unsigned char *tempInBytes = new unsigned char[fileLength];
        fread(&tempInBytes[0], 1, fileLength, f);

        size_t destLength = virtualSize + physicalSize;
        uncompress(&tempBytes[0], (uLongf*)&destLength, &tempInBytes[0], fileLength);

        delete[] tempInBytes;
    }

    char* virtualData = new char[virtualSize];
    memcpy(virtualData, &tempBytes[0], virtualSize);

    char* physicalData = new char[physicalSize];
    memcpy(physicalData, &tempBytes[virtualSize], physicalSize);

    delete[] tempBytes;

    rage::BlockMap* bm = new rage::BlockMap();
    bm->physicalLen = 1;
    bm->virtualLen = 1;

    bm->blocks[0].data = virtualData;
    bm->blocks[0].offset = 0;
    bm->blocks[0].size = virtualSize;

    bm->blocks[1].data = physicalData;
    bm->blocks[1].offset = 0;
    bm->blocks[1].size = physicalSize;

    return bm;
}

template <typename T>
struct ResObjectHandle {
    T *_object;
    rage::BlockMap *_blockMap;
public:
    inline ResObjectHandle(T *_Object, rage::BlockMap *_BlockMap) : _object(_Object), _blockMap(_BlockMap) {}
    inline ~ResObjectHandle() {
        if (_blockMap) {
            for (int i = 0; i < _blockMap->physicalLen + _blockMap->virtualLen; i++)
                delete _blockMap->blocks[i].data;
            delete _blockMap;
        }    
        rage::pgStreamManager::Close();
    }
    inline bool isValid() {
        return _blockMap ? true : false;
    }
    inline T *object() {
        return _object;
    }
};

template <typename T>
inline ResObjectHandle<T> FromResource(const char *resourcePath) {
    rage::pgStreamManager::Open();
    rage::BlockMap* bm = UnwrapRSC5(resourcePath);
    if (!bm)
        return ResObjectHandle<T>(nullptr, nullptr);
    T *obj = (T*)bm->blocks[0].data;
    obj->Resolve(bm);
    return ResObjectHandle<T>(obj, bm);
}