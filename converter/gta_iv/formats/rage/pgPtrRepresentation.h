#pragma once

namespace rage {

struct pgPtrRepresentation {
    unsigned int pointer : 28;
    unsigned int blockType : 4;
};

};