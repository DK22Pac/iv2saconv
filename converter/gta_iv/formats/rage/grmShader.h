#pragma once
#include "pgStreamableBase.h"
#include "grmShaderEffect.h"

namespace rage {

class grmShader : public pgStreamableBase {
protected:
    unsigned char m_version;
    unsigned char m_drawBucket;
    unsigned char m_usageCount;
    unsigned char m_pad;
    unsigned short _fC;
    unsigned short m_shaderIndex;
    unsigned int _f10;
    grmShaderEffect m_effect;

public:
    inline unsigned char GetVersion() { return m_version; }
    inline unsigned short GetShaderIndex() { return m_shaderIndex; }
    inline unsigned char GetUsageCount() { return m_usageCount; }

    inline grmShaderEffect& GetEffect() { return m_effect; }

    inline void Resolve(BlockMap* blockMap = nullptr) {
        m_effect.Resolve(blockMap);
    }

    inline unsigned char GetDrawBucket() { return m_drawBucket; }
};

}