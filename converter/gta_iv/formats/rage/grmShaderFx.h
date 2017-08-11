#pragma once
#include "grmShader.h"

namespace rage {

class grmShaderFx : public grmShader {
private:
public:
    inline void Resolve(BlockMap* blockMap) {
        grmShader::Resolve(blockMap);
    }
};

}