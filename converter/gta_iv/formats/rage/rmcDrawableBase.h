#pragma once
#include "pgBase.h"
#include "grmShaderGroup.h"

namespace rage {

class rmcDrawableBase : public pgBase {
private:
    pgPtr<grmShaderGroup> m_shaderGroup;

public:
    inline grmShaderGroup* GetShaderGroup() { return *m_shaderGroup; }

    inline void Resolve(BlockMap* blockMap) {
        m_shaderGroup.Resolve(blockMap);
        if (!m_shaderGroup.IsNull())
            m_shaderGroup->Resolve(blockMap);
    }
};

}