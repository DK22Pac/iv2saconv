#pragma once
#include "pgStreamableBase.h"
#include "BlockMap.h"

namespace rage {

class grcVertexFormat : public pgStreamableBase {
private:
    struct {
        unsigned int bPosition : 1;
        unsigned int bBlendWeight : 1;
        unsigned int bBlendIndices : 1;
        unsigned int bNormal : 1;
        unsigned int bColor : 1;
        unsigned int bSpecularColor : 1;
        unsigned int bTexCoord1 : 1;
        unsigned int bTexCoord2 : 1;
        unsigned int bTexCoord3 : 1;
        unsigned int bTexCoord4 : 1;
        unsigned int bTexCoord5 : 1;
        unsigned int bTexCoord6 : 1;
        unsigned int bTexCoord7 : 1;
        unsigned int bTexCoord8 : 1;
        unsigned int bTangent : 1;
        unsigned int bBinormal : 1;
    } m_flags;
    unsigned short m_vertexSize;
    unsigned char m_vertexFieldOrder;
    unsigned char m_vertexFieldCount;
    struct {
        unsigned __int64 nPositionType : 4;
        unsigned __int64 nBlendWeightType : 4;
        unsigned __int64 nBlendIndicesType : 4;
        unsigned __int64 nNormalType : 4;
        unsigned __int64 nColorType : 4;
        unsigned __int64 nSpecularColorType : 4;
        unsigned __int64 nTexCoord1Type : 4;
        unsigned __int64 nTexCoord2Type : 4;
        unsigned __int64 nTexCoord3Type : 4;
        unsigned __int64 nTexCoord4Type : 4;
        unsigned __int64 nTexCoord5Type : 4;
        unsigned __int64 nTexCoord6Type : 4;
        unsigned __int64 nTexCoord7Type : 4;
        unsigned __int64 nTexCoord8Type : 4;
        unsigned __int64 nTangentType : 4;
        unsigned __int64 nBinormalType : 4;
    } vertexFields;

public:
    inline unsigned char GetVertexSize() {
        return m_vertexSize;
    }

    inline unsigned char GetFieldCount() {
        return m_vertexFieldCount;
    }

    inline void Resolve(BlockMap* blockMap) {

    }
};

}