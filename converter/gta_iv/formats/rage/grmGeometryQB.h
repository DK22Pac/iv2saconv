#pragma once
#include "datBase.h"
#include "grcIndexBufferD3D.h"
#include "grcVertexBufferD3D.h"

namespace rage {

class grmGeometryQB : public datBase {
private:
    pgPtr<void> m_vertexDeclaration; // actually IDirect3DVertexDeclaration9* at runtime
    unsigned int m_objectType;
    pgPtr<grcVertexBufferD3D> m_vertexBuffers[4];
    pgPtr<grcIndexBufferD3D> m_indexBuffers[4];
    unsigned int m_dwIndexCount;
    unsigned int m_dwFaceCount;
    unsigned short m_wVertexCount;
    unsigned short m_wIndicesPerFace;
    pgPtr<unsigned short> m_boneMapping;
    unsigned short m_vertexStride;
    unsigned short m_boneCount;
    pgPtr<void> m_vertexDeclarationInstance;
    pgPtr<void> m_vertexBufferInstance;
    unsigned int m_useGlobalStreamIndex;

public:
    inline grcVertexBufferD3D* GetVertexBuffer(int idx) {
        return *(m_vertexBuffers[idx]);
    }

    inline grcIndexBufferD3D* GetIndexBuffer(int idx) {
        return *(m_indexBuffers[idx]);
    }

    inline void FixUpBrokenVertexCounts() {
        m_vertexStride = m_vertexBuffers[0]->GetStride();
        m_wVertexCount = m_vertexBuffers[0]->GetCount();

        m_dwIndexCount = m_indexBuffers[0]->GetIndexCount();
        m_dwFaceCount = m_indexBuffers[0]->GetIndexCount() / m_wIndicesPerFace;
    }

    inline void Resolve(BlockMap* blockMap) {
        for (int i = 0; i < 4; i++) {
            m_vertexBuffers[i].Resolve(blockMap);
            if (!m_vertexBuffers[i].IsNull())
                m_vertexBuffers[i]->Resolve(blockMap);
            m_indexBuffers[i].Resolve(blockMap);
            if (!m_indexBuffers[i].IsNull())
                m_indexBuffers[i]->Resolve(blockMap);
        }
        m_boneMapping.Resolve(blockMap);
    }
};

}