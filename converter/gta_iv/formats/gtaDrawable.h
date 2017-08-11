#pragma once
#include "rage\rmcDrawable.h"
#include "rage\pgArray.h"
#include "CLightAttr.h"

class gtaDrawable : public rage::rmcDrawable {
private:
    rage::pgArray<CLightAttr> m_lightAttrs;

public:
    inline void Resolve(rage::BlockMap* blockMap) {
        rmcDrawable::Resolve(blockMap);
        m_lightAttrs.Resolve(blockMap);
    }
};