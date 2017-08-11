#pragma once
#include "pgBase.h"
#include "pgStreamManager.h"

namespace rage {

class grcTexture : public pgBase {
protected:
    unsigned char m_objectType;
    unsigned char m_depth;
    unsigned short m_usageCount;
private:
    int _pad0[2];
protected:
    pgPtr<char> m_name;
    unsigned int m_nativeHandle;
    unsigned short m_width;
    unsigned short m_height;
    unsigned int m_pixelFormat;
    unsigned short m_stride;
    unsigned char m_textureType; // 1 - cube texture, 3 - volume texture, other - regular texture
    unsigned char m_levels;

public:
    inline const char* GetName() {
        return *m_name;
    }

    inline void Resolve(BlockMap* blockMap) {
        m_name.Resolve(blockMap);
    }
};

};