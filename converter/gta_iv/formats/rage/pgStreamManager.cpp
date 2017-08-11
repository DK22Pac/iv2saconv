#include "pgStreamManager.h"
#include "BlockMap.h"
#include "pgPtrRepresentation.h"
#include <unordered_set>

static std::unordered_set<const void*> g_resolvedEntries;

void* rage::pgStreamManager::ResolveFilePointer(pgPtrRepresentation& ptr, BlockMap* blockMap) {
    if (ptr.blockType == 0)
        return nullptr;
    if (blockMap) {
        int startIdx = (ptr.blockType == 5) ? 0 : blockMap->virtualLen;
        int endIdx = (ptr.blockType == 5) ? blockMap->virtualLen : (blockMap->virtualLen + blockMap->physicalLen);
        for (int i = startIdx; i < endIdx; i++) {
            auto& block = blockMap->blocks[i];
            if (ptr.pointer >= block.offset && ptr.pointer < (block.offset + block.size))
                return (char*)block.data + (ptr.pointer - block.offset);
        }
    }
    return nullptr;
}

bool rage::pgStreamManager::IsResolved(const void* ptrAddress) {
    return g_resolvedEntries.find(ptrAddress) != g_resolvedEntries.end();
}

void rage::pgStreamManager::MarkResolved(const void* ptrAddress) {
    g_resolvedEntries.insert(ptrAddress);
}

void rage::pgStreamManager::Open() {
    g_resolvedEntries.clear();
}

void rage::pgStreamManager::Close() {
    g_resolvedEntries.clear();
}