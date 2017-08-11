#pragma once
#include "datBase.h"
#include "pgObjectArray.h"
#include "grmGeometryQB.h"
#include "Vector4.h"

namespace rage {

class grmModel : public datBase
{
private:
    pgObjectArray<grmGeometryQB> m_geometries;
    pgPtr<Vector4> m_geometryBounds;
    pgPtr<unsigned short> m_shaderMappings;
    unsigned short m_boneCount;
    unsigned short m_skinned;
    unsigned short m_pad;
    unsigned short m_zero;
    unsigned short m_zero2;
    struct {
        unsigned short bHasBoneMapping : 1; // bitfield: bit 0 - has bone mapping, bit 1-7: number of geometries with bone mapping
        unsigned short nGeometriesWithBoneMapping : 7;
    } m_nBoneMappingInfo;
    unsigned short m_shaderMappingCount; // may be geometry count by proxy?

public:
    inline pgObjectArray<grmGeometryQB>& GetGeometries() {
        return m_geometries;
    }

    inline Vector4* GetGeometryBounds() {
        return (*m_geometryBounds);
    }

    inline unsigned short* GetShaderMappings() {
        return *m_shaderMappings;
    }

    inline unsigned short GetShaderMappingCount() {
        return m_shaderMappingCount;
    }

    //inline unsigned short CalcDrawBucketMask(grmShaderGroup* shaderGroup) {
    //    unsigned short drawBucketMask = 0xFF00;
    //    for (int i = 0; i < m_shaderMappingCount; i++) {
    //        unsigned short shaderIdx = (*m_shaderMappings)[i];
    //        grmShaderFx* shader = shaderGroup->GetShader(shaderIdx);
    //        drawBucketMask |= (1 << shader->GetDrawBucket());
    //    }
    //    return drawBucketMask;
    //}

    inline void Resolve(BlockMap* blockMap) {
        m_geometries.Resolve(blockMap);
        m_geometryBounds.Resolve(blockMap);
        m_shaderMappings.Resolve(blockMap);
    }
};

}