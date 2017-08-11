#pragma once
#include "grcTexture.h"
#include <string.h>

namespace rage {

class grcTexturePC : public grcTexture {
private:
    float m_28[3];
    float m_34[3];
    unsigned int m_next;
    unsigned int m_prev;
    pgPtr<void> m_pixelData;
private:
    char _pad2[4];

public:
    inline size_t GetDataSize() {
        size_t levelSize = m_stride * m_height;
        size_t size = 0;
        for (int i = 0; i < m_levels; i++) {
            size += levelSize;
            levelSize /= 4;
        }
        return size;
    }

    inline unsigned short GetWidth() {
        return m_width;
    }

    inline unsigned short GetHeight() {
        return m_height;
    }

    inline unsigned short GetStride() {
        return m_stride;
    }

    inline unsigned char GetLevels() {
        return m_levels;
    }

    inline unsigned int GetPixelFormat() {
        return m_pixelFormat;
    }

    inline const void* GetPixelData() {
        return *m_pixelData;
    }

    inline void Resolve(BlockMap* blockMap) {
        grcTexture::Resolve(blockMap);
        m_pixelData.Resolve(blockMap);
    }
};

};