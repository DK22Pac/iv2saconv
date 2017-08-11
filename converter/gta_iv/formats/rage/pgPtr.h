#pragma once
#include "pgStreamableBase.h"
#include "pgPtrRepresentation.h"
#include "pgStreamManager.h"

namespace rage {

template<typename T>
class pgPtr : public pgStreamableBase {
public:
    union {
        pgPtrRepresentation on_disk;
        T* pointer;
    };

public:
    T* operator->() const {
        if (pgStreamManager::IsResolved(this))
            return (T*)pointer;
        return (T*)pgStreamManager::ResolveFilePointer(const_cast<pgPtrRepresentation&>(on_disk));
    }

    T* operator*() const {
        if (pgStreamManager::IsResolved(this))
            return (T*)pointer;
        return (T*)pgStreamManager::ResolveFilePointer(const_cast<pgPtrRepresentation&>(on_disk));
    }

    pgPtr operator=(T* other) {
        pointer = other;
        pgStreamManager::MarkResolved(this);
        return *this;
    }

    pgPtr(pgPtrRepresentation fromRep) {
        on_disk = fromRep;
    }

    pgPtr(const pgPtr& from) {
        if (pgStreamManager::IsResolved(&from))
            pgStreamManager::MarkResolved(this);
        on_disk = from.on_disk;
    }

    pgPtr& operator=(const pgPtr& arg) {
        if (pgStreamManager::IsResolved(&arg))
            pgStreamManager::MarkResolved(this);
        pointer = arg.pointer;
        return *this;
    }

    bool IsNull() {
        return (pointer == 0);
    }

    void Resolve(BlockMap* blockMap) {
        if (on_disk.blockType == 0 && on_disk.pointer == 0)
            return;
        if (!pgStreamManager::IsResolved(this)) {
            bool physical = (on_disk.blockType == 6);
            pointer = (T*)pgStreamManager::ResolveFilePointer(on_disk, blockMap);
            pgStreamManager::MarkResolved(this);
        }
    }
};

}