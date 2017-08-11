#pragma once
#include "pgPtrRepresentation.h"

namespace rage {

struct BlockMap;

class pgStreamManager {
public:
    static void* ResolveFilePointer(pgPtrRepresentation& ptr, BlockMap* blockMap = nullptr);
    static bool IsResolved(const void* ptrAddress);
    static void MarkResolved(const void* ptrAddress);
    static void Open();
    static void Close();
};

};