//
// Created by Benjamin Lee on 8/18/24.
//

#ifndef VEX_PATH_PLANNER_FRESNEL_H
#define VEX_PATH_PLANNER_FRESNEL_H

#include "MathUtils.h"
#include "Vector2.h"

#pragma once

#define FRESNEL_TABLE_SIZE 5000

namespace path {
    extern Vector2 FRESNEL_TABLE[FRESNEL_TABLE_SIZE];
    extern void init_fresnel();
    extern double fresnel_C(double s);
    extern double fresnel_S(double s);
    extern Vector2 fresnel_vec(double s);
}
#endif //VEX_PATH_PLANNER_FRESNEL_H
