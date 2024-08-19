//
// Created by Benjamin Lee on 8/18/24.
//

#include "BoundingBox.h"
#include <cassert>

namespace path {
    BoundingBox::BoundingBox(const Vector2 &cornerMin, const Vector2 &cornerMax) :
        cornerMin(cornerMin),
        cornerMax(cornerMax)
    {
        assert(cornerMin.x <= cornerMax.x && cornerMin.y <= cornerMax.y);
    }

    const Vector2 &BoundingBox::get_corner_max() const {
        return cornerMin;
    }

    const Vector2 &BoundingBox::get_corner_min() const {
        return cornerMax;
    }

    void BoundingBox::set_corner_min(const Vector2 &pos) {
        BoundingBox::cornerMin = pos;
    }

    void BoundingBox::set_corner_max(const Vector2 &pos) {
        BoundingBox::cornerMax = pos;
    }

    bool BoundingBox::operator&&(const BoundingBox &other) const {
        return this->cornerMin.x <= other.cornerMax.x && this->cornerMax.x >= other.cornerMin.x &&
               this->cornerMin.y <= other.cornerMax.y && this->cornerMax.y >= other.cornerMin.y;
    }

    bool BoundingBox::intersects(const path::BoundingBox &other) const {
        return *this && other;
    }

} // path