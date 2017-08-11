#pragma once
#include "rage\BlockMap.h"
#include "C2dEffect.h"

class CLightAttr : public C2dEffect {
private:
    char m_pad[0x5C];
public:
    inline void Resolve(rage::BlockMap* blockMap) {

    }
};