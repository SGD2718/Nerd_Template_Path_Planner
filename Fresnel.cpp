//
// Created by Benjamin Lee on 8/18/24.
//

#include "Fresnel.h"

namespace math {
    Vector2 FRESNEL_TABLE[FRESNEL_TABLE_SIZE];

    void init_fresnel() {
        auto tmp = moving_integral<double, Vector2>([](double x) -> Vector2 {
            return {cos(M_PI_2 * x * x),  sin(M_PI_2 * x * x)};
        }, 0, 1, FRESNEL_TABLE_SIZE);

        std::copy(tmp.begin(), tmp.end(), FRESNEL_TABLE);
    }
}