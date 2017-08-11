#pragma once
#include "datBase.h"
#include "pgPtr.h"
#include "pgDictionary.h"
#include "grcTexturePC.h"
#include "grmShaderFx.h"

namespace rage {

class grmShaderGroup : public datBase {
private:
    pgPtr<pgDictionary<grcTexturePC>> m_textures;
    pgObjectArray<grmShaderFx> m_shaders;
    pgObjectArray<int> _f10;
    pgObjectArray<int> _f18;
    pgObjectArray<int> _f20;
    pgArray<int> _f28;
    pgArray<int> _f30;
    pgObjectArray<int> _f38;
    pgArray<unsigned int> m_vertexFormats;
    pgArray<unsigned int> m_shaderIndices;

public:
    inline pgDictionary<grcTexturePC>* GetTextures() { return *m_textures; }

    inline unsigned short GetNumShaders() {
        return m_shaders.GetCount();
    }

    inline grmShaderFx* GetShader(unsigned short offset) { return m_shaders.Get(offset); }

    inline unsigned int GetVertexFormat(unsigned short offset) { return m_vertexFormats.Get(offset); }

    inline unsigned int GetShaderIndex(unsigned short offset) {
        return m_shaderIndices.Get(offset);
    }

    inline void Resolve(BlockMap* blockMap) {
        m_textures.Resolve(blockMap);
        if (!m_textures.IsNull())
            m_textures->Resolve(blockMap);
        m_shaders.Resolve(blockMap);
        m_vertexFormats.Resolve(blockMap);
        m_shaderIndices.Resolve(blockMap);
    }
};

}