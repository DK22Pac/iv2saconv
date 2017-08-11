#pragma once
#include "pgPtr.h"
#include "pgStreamManager.h"
#include <algorithm>

namespace rage {

template<typename TValue>
class pgObjectArray : public pgStreamableBase {
private:
    pgPtr<pgPtr<TValue>> m_objects;
    unsigned short m_count;
    unsigned short m_size;

public:
    TValue* Get(uint16_t offset) {
        if (offset >= m_count)
            return nullptr;
        return *((*m_objects)[offset]);
    }

    unsigned short GetSize() const {
        return m_size;
    }

    unsigned short GetCount() const {
        return m_count;
    }

    void Resolve(BlockMap* blockMap) {
        m_objects.Resolve(blockMap);
        for (int i = 0; i < m_size; i++) {
            (*m_objects)[i].Resolve(blockMap);
            (*m_objects)[i]->Resolve(blockMap);
        }
    }
};

};