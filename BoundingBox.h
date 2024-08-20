//
// Created by Benjamin Lee on 8/18/24.
//

#ifndef VEX_PATH_PLANNER_BOUNDINGBOX_H
#define VEX_PATH_PLANNER_BOUNDINGBOX_H

#include "Vector2.h"

namespace path {
    class BoundingBox {
    public:
        BoundingBox(const Vector2 &cornerMin, const Vector2 &cornerMax);

        void set_corner_min(const Vector2 &pos);
        void set_corner_max(const Vector2 &pos);

        [[nodiscard]] const Vector2 &get_corner_max() const;
        [[nodiscard]] const Vector2 &get_corner_min() const;

        [[nodiscard]] bool intersects(const BoundingBox& other) const;

        /**
         * @brief check for intersections
         * @param other another bounding box
         * @return whether two bounding boxes intersect
         */
        bool operator&&(const BoundingBox& other) const;

    private:
        Vector2 cornerMin; // (xMin, yMin)
        Vector2 cornerMax; // (xMax, yMax)
    };

} // path

#endif //VEX_PATH_PLANNER_BOUNDINGBOX_H
