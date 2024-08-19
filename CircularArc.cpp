//
// Created by Benjamin Lee on 8/18/24.
//

#include "CircularArc.h"

namespace path {
    CircularArc::CircularArc(path::Vector2 center, double startAngle, double endAngle, double radius, bool visible):
            Curve(visible),
            center(center),
            thetaStart(startAngle),
            thetaEnd(endAngle),
            radius(radius)
        {}

    Vector2 CircularArc::get_point(double s) const {
        if (this->thetaStart <= this->thetaEnd)
            s = this->thetaStart + s / this->radius;
        else
            s = this->thetaStart - s / this->radius;
        return {this->radius * cos(s), this->radius * sin(s)};
    }

    std::vector<Vector2> CircularArc::get_waypoints(int numWaypoints) const {
        return map_interval<double, Vector2>([this](double t) -> Vector2 {
            return Vector2(cos(t), sin(t)) * this->radius + this->center;
        }, this->thetaStart, this->thetaEnd, numWaypoints);
    }

    std::vector<Vector2> CircularArc::get_waypoints_spaced(double ds) const {
        return map_interval_spaced<double, Vector2>([this](double t) -> Vector2 {
            return Vector2(cos(t), sin(t)) * this->radius + this->center;
        }, this->thetaStart, this->thetaEnd, ds / this->radius);
    }

    Vector2 CircularArc::get_center() const {
        return this->center;
    }

    double CircularArc::get_start_angle() const {
        return this->thetaStart;
    }

    double CircularArc::get_end_angle() const {
        return this->thetaEnd;
    }

    double CircularArc::get_radius() const {
        return this->radius;
    }

    void CircularArc::set_center(path::Vector2 pos) {
        this->center = pos;
    }

    void CircularArc::set_start_angle(double theta) {
        this->thetaStart = theta;
    }

    void CircularArc::set_end_angle(double theta) {
        this->thetaEnd = theta;
    }

    void CircularArc::set_radius(double r) {
        this->radius = r;
    }

    void CircularArc::configure(path::Vector2 center, double startAngle, double endAngle, double r) {
        this->center = center;
        this->thetaStart = startAngle;
        this->thetaEnd = endAngle;
        this->radius = r;
    }
} // path