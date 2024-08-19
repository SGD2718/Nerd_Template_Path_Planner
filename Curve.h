//
// Created by Benjamin Lee on 8/17/24.
//

#ifndef VEX_PATH_PLANNER_CURVE_H
#define VEX_PATH_PLANNER_CURVE_H

#include <cmath>
#include <vector>
#include "Vector2.h"
#include "MathUtils.h"

namespace math {

    class Curve {
    public:
        explicit Curve(bool visible = true);

        [[nodiscard]] virtual Vector2 get_point(double s) const;
        [[nodiscard]] virtual std::vector<Vector2> get_waypoints(int numPoints) const;
        [[nodiscard]] virtual std::vector<Vector2> get_waypoints_spaced(double ds) const;

        [[nodiscard]] bool is_visible() const;

        void set_visibility(bool visibility);

    private:
        bool visible;
    };
} // path

#endif //VEX_PATH_PLANNER_CURVE_H
