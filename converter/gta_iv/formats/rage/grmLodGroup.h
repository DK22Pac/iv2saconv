#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "grmModel.h"

namespace rage {

class grmLodGroup {
private:
    Vector4 m_center;
    Vector3 m_boundsMin;
    Vector3 m_boundsMax;
    pgPtr<pgObjectArray<grmModel>> m_models[4];
    float m_9999[4];
    int m_drawBucketMask[4]; // does this apply to five?

public:
    inline Vector3 GetBoundsMin() {
        return m_boundsMin;
    }

    inline Vector3 GetBoundsMax() {
        return m_boundsMax;
    }

    inline Vector3 GetCenter() {
        return { m_center.x, m_center.y, m_center.z };
    }

    inline float GetRadius() {
        return m_center.w;
    }

    inline grmModel* GetModel(int idx) {
        if (idx < 0 || idx >= _countof(m_models))
            abort();
        if (m_models[idx].IsNull())
            return nullptr;
        return m_models[idx]->Get(0);
    }

    inline pgObjectArray<grmModel>* GetPrimaryModel() {
        return *m_models[0];
    }

    inline void Resolve(BlockMap* blockMap) {
        for (int i = 0; i < 4; i++) {
            m_models[i].Resolve(blockMap);
            if (!m_models[i].IsNull())
                m_models[i]->Resolve(blockMap);
        }
    }
};

}