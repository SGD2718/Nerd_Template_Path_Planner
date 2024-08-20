//
// Created by Benjamin Lee on 8/18/24.
//

#include "Joint.h"
#include "Fresnel.h"

namespace path {
    Joint::Joint(Vector2 *pStart, Vector2 *pMiddle, Vector2 *pEnd, double sharpness, double maxCurvature) :
            pStart(pStart), pMiddle(pMiddle), pEnd(pEnd), sharpness(sharpness), maxCurvature(maxCurvature) {
        this->update();
    }

    void Joint::update() {
        auto e1 = (*pMiddle - *pStart).normalize();
        auto e2 = (*pEnd - *pMiddle).normalize();
        auto delta0 = e1.heading();
        auto delta = e1.oriented_angle(e2);
        auto deltaAbs = fabs(delta);
        auto curvature = std::fmin(this->maxCurvature, sqrt(deltaAbs * sharpness));
        auto deltaMin = curvature * curvature / sharpness;

        double length;
        double d;

        if (fabs(delta) > deltaMin) { // circle in the middle
            length = curvature / this->sharpness;
            auto tmp = fresnel_vec(curvature / sqrt(this->sharpness * M_PI)) * sqrt(M_PI / this->sharpness);
            auto tmp2 = curvature * curvature / (2 * this->sharpness);
            auto r = 1 / curvature;
            auto h = tmp.y + cos(tmp2) * r;

            d = tmp.x - sin(tmp2) * r;
            auto O = Vector2(d, sign(delta) * h).rotate(delta0);
            d += h * tan(deltaAbs / 2);
            O += *this->pMiddle - d * e1;
            this->arc.set_visibility(true);
            this->arc.set_radius(r);
            this->arc.set_center(O);

            if (delta > deltaMin) {
                this->arc.set_start_angle(delta0 + (deltaMin - M_PI) / 2);
                this->arc.set_end_angle(delta0 + deltaAbs - (deltaMin + M_PI) / 2);
            } else {
                this->arc.set_start_angle(delta0 - (deltaMin - M_PI) / 2);
                this->arc.set_end_angle(delta0 - deltaAbs + (deltaMin + M_PI) / 2);
            }
        } else {
            length = sqrt(fabs(delta) / sharpness);
            auto tmp = fresnel_vec(deltaAbs / M_PI) * sqrt(M_PI / this->sharpness);
            d = tmp.x + tmp.y * tan(deltaAbs / 2);
            this->arc.set_visibility(false);
        }

        auto clothoid1Start = *this->pMiddle - e1 * d;
        auto clothoid2Start = *this->pMiddle + e2 * d;

        this->clothoid1.configure(clothoid1Start, delta0, length, sharpness * sign(delta));
        this->clothoid2.configure(clothoid2Start, delta0 + delta + M_PI, length, -sharpness * sign(delta), 0, true);
        this->line1.configure(*this->pStart, clothoid1Start);
        this->line2.configure(clothoid2Start, *this->pEnd);
    }

    std::vector<Vector2> Joint::get_waypoints(double ds) const {
        std::vector<Vector2> res;
        auto length = line1.get_length() + this->line2.get_length() + this->clothoid1.get_length() +
                      this->clothoid2.get_length() + this->arc.get_length();
        res.reserve((unsigned long)(length / ds) + 8 + this->arc.is_visible() * 2);
        this->line1.get_waypoints_spaced(res, ds);
        this->clothoid1.get_waypoints_spaced(res, ds);
        if (this->arc.is_visible())
            this->arc.get_waypoints_spaced(res, ds);
        this->clothoid2.get_waypoints_spaced(res, ds);
        this->line2.get_waypoints_spaced(res, ds);
        return res;
    }
} // path