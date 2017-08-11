#pragma once
#include "datBase.h"
#include "pgPtr.h"

namespace rage {

class grcIndexBuffer : public datBase {
private:
    unsigned int m_indexCount;
    pgPtr<unsigned short> m_indexData;

public:
    inline unsigned short* GetIndexData() {
        return *m_indexData;
    }

    inline unsigned short GetIndexCount() {
        return m_indexCount;
    }

    inline void Resolve(BlockMap* blockMap) {
        m_indexData.Resolve(blockMap);
    }
};

}