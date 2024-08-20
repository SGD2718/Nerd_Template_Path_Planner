//
// Created by Benjamin Lee on 8/18/24.
//

#include "Line.h"

namespace path {
    Line::Line(path::Vector2 start, path::Vector2 end, bool visible):
            Curve(visible),
            start(start),
            end(end)
    {}

    Vector2 Line::get_point(double s) const {
        return start + (end - start).normalize() * s;
    }

    void Line::get_waypoints(std::vector<path::Vector2>& output, int numWaypoints) const {
        map_interval<double, Vector2>(output, [this](double s) -> Vector2 {
            return lerp<double, Vector2>(this->start, this->end, s);
        }, 0, 1, numWaypoints);
    }

    void Line::get_waypoints_spaced(std::vector<path::Vector2>& output, double ds) const {
        auto unitVec = (end - start).normalize();
        map_interval_spaced<double, Vector2>(output, [this, unitVec](double s) -> Vector2 {
            return this->start + unitVec * s;
        }, 0, (this->end - this->start).norm(), ds);
    }

    Vector2 Line::get_start() const {
        return this->start;
    }

    Vector2 Line::get_end() const {
        return this->end;
    }

    double Line::get_length() const {
        return (this->end - this->start).norm();
    }

    void Line::set_start(path::Vector2 pos) {
        this->start = pos;
    }

    void Line::set_end(path::Vector2 pos) {
        this->end = pos;
    }

    void Line::configure(path::Vector2 a, path::Vector2 b) {
        this->start = a;
        this->end = b;
    }
} // path