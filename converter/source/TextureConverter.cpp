#include "TextureConverter.h"
#include "Log.h"
#include "gta_iv\ResourceReader.h"
#include "dffapi\texture_helper.h"
#include "dffapi\Memory.h"

bool TextureConverter::Convert(const std::string &sourceFilePath, const std::string &destFilePath, ConverterOptions const &options) {
    auto wtdHandle = FromResource<rage::pgDictionary<rage::grcTexturePC>>(sourceFilePath.c_str());
    if (wtdHandle.isValid()) {
        auto wtd = wtdHandle.object();
        gtaRwTexDictionary txd;
        if (options.texturesPacking.sliceLevels && options.texturesPacking.baseLevel != 0)
            WtdToTxd(wtd, &txd, options.texturesPacking.baseLevel);
        else
            WtdToTxd(wtd, &txd);
        gtaRwStream *stream = gtaRwStreamOpen(rwSTREAMFILENAME, rwSTREAMWRITE, destFilePath.c_str());
        if (stream) {
            txd.StreamWrite(stream);
            gtaRwStreamClose(stream);
            txd.Destroy();
            return true;
        }
        txd.Destroy();
    }
    return false;
}

void TextureConverter::SetTextureName(char *outputTxdTextureName, char const *wtdTextureName) {
    size_t len = strlen(wtdTextureName);
    size_t numCharsToCopy = len;
    size_t posToCopy = 0;
    if (!strncmp(wtdTextureName, "pack:/", 6)) {
        posToCopy = 6;
        numCharsToCopy -= 6;
    }
    if (!strncmp(&wtdTextureName[len - 4], ".dds", 4))
        numCharsToCopy -= 4;
    size_t numCharsToCopyFinal = numCharsToCopy;
    if (numCharsToCopyFinal > 31)
        numCharsToCopyFinal = 31;
    strncpy(outputTxdTextureName, &wtdTextureName[posToCopy], numCharsToCopyFinal);
    outputTxdTextureName[numCharsToCopyFinal] = '\0';
    if (numCharsToCopy != numCharsToCopyFinal) {
        char *tmpName = new char[numCharsToCopy + 1];
        strncpy(tmpName, &wtdTextureName[posToCopy], numCharsToCopy);
        tmpName[numCharsToCopy] = '\0';
        lout << warning << "texture " << q << tmpName << q << " has too long name (renamed to " << q << outputTxdTextureName << q << ")" << nl;
        delete[] tmpName;
    }
}

void TextureConverter::WtdToTxd(rage::pgDictionary<rage::grcTexturePC> *wtd, gtaRwTexDictionary *txd) {
    if (wtd->GetCount() > 0) {
        txd->Initialise(wtd->GetCount());
        unsigned int i = 0;
        for (const auto &entry : *wtd) {
            rage::grcTexturePC &tex = *entry.second;
            char textureName[32];
            SetTextureName(textureName, tex.GetName());
            unsigned int format = GetFormatRwFormat((D3DFORMAT)tex.GetPixelFormat());
            if (tex.GetLevels() > 1)
                format |= rwRASTERFORMATMIPMAP;
            txd->textures[i].Initialise(rwID_PCD3D9, tex.GetLevels() > 1 ? rwFILTERLINEARMIPLINEAR : rwFILTERLINEAR, rwTEXTUREADDRESSWRAP,
                rwTEXTUREADDRESSWRAP, textureName, NULL, format, tex.GetPixelFormat(), tex.GetWidth(), tex.GetHeight(),
                GetFormatDepth((D3DFORMAT)tex.GetPixelFormat()), tex.GetLevels(), 4, GetFormatHasAlpha((D3DFORMAT)tex.GetPixelFormat()), false,
                false, GetFormatIsCompressed((D3DFORMAT)tex.GetPixelFormat()));
            unsigned int total = 0;
            for (int j = 0; j < tex.GetLevels(); j++) {
                txd->textures[i].levels[j].size = (tex.GetStride() * tex.GetHeight()) >> (j * 2);
                txd->textures[i].levels[j].pixels = (gtaRwUInt8 *)gtaMemAlloc(txd->textures[i].levels[j].size);
                memcpy(txd->textures[i].levels[j].pixels, &reinterpret_cast<const unsigned char *>(tex.GetPixelData())[total],
                    txd->textures[i].levels[j].size);
                total += txd->textures[i].levels[j].size;
            }
            i++;
        }
    }
    else
        txd->Initialise(0);
}

void TextureConverter::WtdToTxd(rage::pgDictionary<rage::grcTexturePC> *wtd, gtaRwTexDictionary *txd, unsigned int startLevel) {
    if (wtd->GetCount() > 0) {
        txd->Initialise(wtd->GetCount());
        unsigned int i = 0;
        for (const auto &entry : *wtd) {
            rage::grcTexturePC &tex = *entry.second;
            char textureName[32];
            SetTextureName(textureName, tex.GetName());
            unsigned int format = GetFormatRwFormat((D3DFORMAT)tex.GetPixelFormat());
            unsigned int total = 0;
            unsigned int width = tex.GetWidth();
            unsigned int height = tex.GetHeight();
            unsigned int levels = tex.GetLevels();
            unsigned int base_level = startLevel;
            if (base_level >= tex.GetLevels())
                base_level = tex.GetLevels() - 1;
            levels -= base_level;
            for (int j = 0; j < base_level; j++) {
                width /= 2;
                if (!width)
                    width = 1;
                height /= 2;
                if (!height)
                    height = 1;
                total += (tex.GetStride() * tex.GetHeight()) >> (j * 2);
            }
            if (levels > 1)
                format |= rwRASTERFORMATMIPMAP;
            txd->textures[i].Initialise(rwID_PCD3D9, levels > 1 ? rwFILTERLINEARMIPLINEAR : rwFILTERLINEAR, rwTEXTUREADDRESSWRAP, rwTEXTUREADDRESSWRAP,
                textureName, NULL, format, tex.GetPixelFormat(), width, height, GetFormatDepth((D3DFORMAT)tex.GetPixelFormat()), levels, 4,
                GetFormatHasAlpha((D3DFORMAT)tex.GetPixelFormat()), false, false, GetFormatIsCompressed((D3DFORMAT)tex.GetPixelFormat()));
            unsigned int level = 0;
            for (int j = base_level; j < tex.GetLevels(); j++) {
                txd->textures[i].levels[level].size = (tex.GetStride() * tex.GetHeight()) >> (j * 2);
                txd->textures[i].levels[level].pixels = (gtaRwUInt8 *)gtaMemAlloc(txd->textures[i].levels[level].size);
                memcpy(txd->textures[i].levels[level].pixels, &reinterpret_cast<const unsigned char *>(tex.GetPixelData())[total],
                    txd->textures[i].levels[level].size);
                total += txd->textures[i].levels[level].size;
                level++;
            }
            i++;
        }
    }
    else
        txd->Initialise(0);
}