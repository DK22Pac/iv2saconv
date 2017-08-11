#pragma once
#include "datBase.h"
#include "grcVertexFormat.h"
#include "pgPtr.h"

namespace rage {

class grcVertexBuffer : public datBase {
private:
    unsigned short m_vertexCount;
    unsigned char m_locked;
    char m_pad;
    pgPtr<void> m_lockedData;
    unsigned int m_vertexSize;
    pgPtr<grcVertexFormat> m_vertexFormat;
    unsigned int m_lockThreadId;
    pgPtr<void> m_vertexData;

public:
    inline grcVertexFormat* GetVertexFormat() {
        return *m_vertexFormat;
    }

    inline void* GetVertices() {
        return *m_vertexData;
    }

    
    inline unsigned int GetStride() {
        return m_vertexSize;
    }

    inline unsigned int GetCount() {
        return m_vertexCount;
    }

    inline void Resolve(BlockMap* blockMap) {
        m_lockedData.Resolve(blockMap);
        m_vertexData.Resolve(blockMap);
        m_vertexFormat.Resolve(blockMap);
        if (!m_vertexFormat.IsNull())
            m_vertexFormat->Resolve(blockMap);
    }
};

}