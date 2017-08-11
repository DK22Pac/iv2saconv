#pragma once
#include "pgPtr.h"
#include "pgStreamManager.h"
#include <algorithm>

namespace rage {

template<typename TValue, typename TIndex = unsigned short>
class pgArray : public pgStreamableBase {
private:
    pgPtr<TValue> m_offset;
    TIndex m_count;
    TIndex m_size;

public:
    TValue& Get(TIndex offset) {
        return (*m_offset)[offset];
    }

    TIndex GetSize() const {
        return m_size;
    }

    TIndex GetCount() const {
        return m_count;
    }

    void Resolve(BlockMap* blockMap) {
        m_offset.Resolve(blockMap);
    }
};

};