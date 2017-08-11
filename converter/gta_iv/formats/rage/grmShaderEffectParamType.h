#pragma once

namespace rage {

enum class grmShaderEffectParamType : unsigned char {
    Texture = 0,
    Vector4 = 1,
    Matrix = 4,
    Vector4x6 = 8,
    Vector4x14 = 14,
    Vector4x15 = 15,
    Vector4x16 = 16
};

}