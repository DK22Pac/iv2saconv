#pragma once
#include "pgPtr.h"
#include "pgBase.h"
#include "pgArray.h"
#include "pgObjectArray.h"
#include "..\..\Hash.h"
#include <algorithm>
#include <vector>

namespace rage {

template<typename TValue>
class pgDictionary : public pgBase {
private:
    pgPtr<pgBase> m_parent;
    unsigned int m_usageCount;
    pgArray<unsigned int> m_hashes;
    pgObjectArray<TValue> m_values;

public:
    struct iterator : public std::iterator<std::forward_iterator_tag, std::pair<uint32_t, TValue*>> {
    private:
        pgDictionary* m_base;
        int m_index;
        std::pair<uint32_t, TValue*> m_value;

    private:
        std::pair<uint32_t, TValue*> GetValue() {
            return std::make_pair(m_base->m_hashes.Get(m_index), m_base->m_values.Get(m_index));
        }

    public:
        iterator(pgDictionary* base, int index) : m_base(base), m_index(index) {
            m_value = GetValue();
        }

        std::pair<uint32_t, TValue*> operator*() const {
            return m_value;
        }

        const std::pair<uint32_t, TValue*>* operator->() const {
            return &m_value;
        }

        const iterator& operator++() {
            m_index++;
            m_value = GetValue();
            return *this;
        }

        friend bool operator!=(const iterator& left, const iterator& right) {
            return (left.m_base != right.m_base || left.m_index != right.m_index);
        }

        friend bool operator==(const iterator& left, const iterator& right) {
            return !(left != right);
        }
    };

public:
    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, m_hashes.GetCount());
    }

    TValue* Get(uint32_t keyHash) {
        for (int i = 0; i < m_hashes.GetCount(); i++) {
            if (m_hashes.Get(i) == keyHash)
                return m_values.Get(i);
        }
        return nullptr;
    }

    TValue* Get(const char* key) {
        return Get(HashString(key));
    }

    unsigned short GetCount() const {
        return m_hashes.GetCount();
    }

    void Resolve(BlockMap* blockMap) {
        m_parent.Resolve(blockMap);
        m_hashes.Resolve(blockMap);
        m_values.Resolve(blockMap);
    }
};

};