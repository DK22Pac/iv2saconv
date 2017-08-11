#pragma once
#include <math.h>

namespace rage {

class Vector3 {
public:
    float x, y, z;

    private:
        float __pad;

public:
    Vector3(float x, float y, float z) : x(x), y(y), z(z), __pad(NAN) {}

    Vector3() : Vector3(0.0f, 0.0f, 0.0f) {}
};

}