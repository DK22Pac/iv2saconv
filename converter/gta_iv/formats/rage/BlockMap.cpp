#include "BlockMap.h"
#include <string.h>

rage::BlockMap::BlockMap() {
    virtualLen = 0;
    physicalLen = 0;
    memset(blocks, 0, sizeof(blocks));
}