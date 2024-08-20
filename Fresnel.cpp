//
// Created by Benjamin Lee on 8/18/24.
//

#include "Fresnel.h"
#include "MathUtils.h"

namespace path {
    Vector2 FRESNEL_TABLE[FRESNEL_TABLE_SIZE];

    void init_fresnel() {
        auto tmp = moving_integral<double, Vector2>([](double x) -> Vector2 {
            return {cos(M_PI_2 * x * x),  sin(M_PI_2 * x * x)};
        }, 0, 1, FRESNEL_TABLE_SIZE);

        std::copy(tmp.begin(), tmp.end(), FRESNEL_TABLE);
    }

    double fresnel_C(double s) {
        assert(s <= 1);

        if (s == 1)
            return FRESNEL_TABLE[FRESNEL_TABLE_SIZE - 1].x;

        auto t = s * FRESNEL_TABLE_SIZE;
        auto idx = (int)t;

        t -= idx;
        return lerp<double, double>(FRESNEL_TABLE[idx].x, FRESNEL_TABLE[idx + 1].x, t);
    }

    double fresnel_S(double s) {
        assert(s <= 1);

        if (s == 1)
            return FRESNEL_TABLE[FRESNEL_TABLE_SIZE - 1].y;

        auto t = s * FRESNEL_TABLE_SIZE;
        auto idx = (int)t;

        t -= idx;
        return lerp<double, double>(FRESNEL_TABLE[idx].y, FRESNEL_TABLE[idx + 1].y, t);
    }

    Vector2 fresnel_vec(double s) {
        assert(s <= 1);

        if (s == 1)
            return FRESNEL_TABLE[FRESNEL_TABLE_SIZE - 1];

        auto t = s * FRESNEL_TABLE_SIZE;
        auto idx = (int)t;
        t -= idx;
        return lerp<double, Vector2>(FRESNEL_TABLE[idx], FRESNEL_TABLE[idx + 1], t);
    }
}