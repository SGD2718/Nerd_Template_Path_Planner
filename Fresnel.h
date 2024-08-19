//
// Created by Benjamin Lee on 8/18/24.
//

#ifndef VEX_PATH_PLANNER_FRESNEL_H
#define VEX_PATH_PLANNER_FRESNEL_H

#include "MathUtils.h"
#include "Vector2.h"

#pragma once

#define FRESNEL_TABLE_SIZE 1000

namespace math {
    extern Vector2 FRESNEL_TABLE[FRESNEL_TABLE_SIZE];
    extern void init_fresnel();
}
#endif //VEX_PATH_PLANNER_FRESNEL_H
