#pragma once
#include "grcIndexBuffer.h"

namespace rage {

class grcIndexBufferD3D : public grcIndexBuffer {
private:
    void* m_pIIndexBuffer;
    int m_unk[8];

public:
    inline void Resolve(BlockMap* blockMap ) {
        grcIndexBuffer::Resolve(blockMap);
    }
};

}