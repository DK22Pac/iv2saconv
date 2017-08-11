#pragma once
#include "rmcDrawableBase.h"
#include "crSkeletonData.h"
#include "grmLodGroup.h"

namespace rage {

class rmcDrawable : public rmcDrawableBase {
private:
    pgPtr<crSkeletonData> m_skeletonData;
    grmLodGroup m_lodGroup;

public:
    inline grmLodGroup& GetLodGroup() {
        return m_lodGroup;
    }

    inline void Resolve(BlockMap* blockMap) {
        rmcDrawableBase::Resolve(blockMap);
        m_skeletonData.Resolve(blockMap);
        if (!m_skeletonData.IsNull())
            m_skeletonData->Resolve(blockMap);
        m_lodGroup.Resolve(blockMap);
    }
};

}