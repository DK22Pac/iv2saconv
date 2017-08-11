#pragma once
#include "pgStreamableBase.h"
#include "ResourceFlags.h"

namespace rage {

struct BlockMap : public pgStreamableBase {
    unsigned short virtualLen;
    unsigned short physicalLen;

    struct BlockInfo {
        unsigned int offset;
        void* data;
        unsigned int size;
    } blocks[128];

    size_t baseAllocationSize[2];

    BlockMap();
};

}