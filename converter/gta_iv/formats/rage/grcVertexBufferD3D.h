#pragma once
#include "grcVertexBuffer.h"

namespace rage {

class grcVertexBufferD3D : public grcVertexBuffer
{
private:
    void* m_pIVertexBuffer;
    int m_unk[8];

public:
    inline void Resolve(BlockMap* blockMap) {
        grcVertexBuffer::Resolve(blockMap);
    }
};

}