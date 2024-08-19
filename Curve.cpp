//
// Created by Benjamin Lee on 8/18/24.
//

#include "Curve.h"

namespace path {
    Curve::Curve(bool visible) :
            visible(visible) {}

    Vector2 Curve::get_point(double s) const {
        throw std::logic_error("Curve.get_point(double s) is not implemented");
    }

    std::vector<Vector2> Curve::get_waypoints(int numPoints) const {
        throw std::logic_error("Curve.get_waypoints(int numWaypoints) is not implemented");
    }

    std::vector<Vector2> Curve::get_waypoints_spaced(double ds) const {
        throw std::logic_error("Curve.get_waypoints_spaced(double ds) is not implemented");
    }

    bool Curve::is_visible() const {
        return this->visible;
    }

    void Curve::set_visibility(bool visibility) {
        this->visible = visibility;
    }
}