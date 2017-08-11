#pragma once
#include "pgPtr.h"
#include "grmShaderEffectParamType.h"

namespace rage {

class grmShaderEffect {
private:
    pgPtr<pgPtr<void>> m_parameters;
    pgPtr<int> m_pNull;
    unsigned int m_parameterCount;
    unsigned int m_parameterDataSize;
    pgPtr<grmShaderEffectParamType> m_parameterTypes;
    unsigned int m_shaderHash;
    unsigned int _f2C;
    unsigned int _f30;
    pgPtr<unsigned int> m_parameterNameHashes;
    unsigned int _f38;
    unsigned int _f3C;
    unsigned int _f40;

public:
    inline unsigned int GetParameterDataSize() {
        return m_parameterDataSize;
    }

    inline unsigned int GetShaderHash() {
        return m_shaderHash;
    }

    inline unsigned int GetParameterCount() {
        return m_parameterCount;
    }

    inline unsigned int GetParameterNameHash(int idx) {
        return (*m_parameterNameHashes)[idx];
    }

    inline void* GetParameterValue(int idx) {
        return *((*m_parameters)[idx]);
    }

    inline void Resolve(BlockMap* blockMap) {
        m_parameters.Resolve(blockMap);
        m_parameterNameHashes.Resolve(blockMap);
        m_parameterTypes.Resolve(blockMap);
        auto count = GetParameterCount();
        for (int i = 0; i < count; i++)
            (*m_parameters)[i].Resolve(blockMap);
    }
};

}