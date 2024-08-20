//
// Created by Benjamin Lee on 8/18/24.
//

#include "Clothoid.h"
#include "Fresnel.h"

namespace path {

    Clothoid::Clothoid(path::Vector2 initialPosition, double initialHeading, double length, double sharpness,
                       double initialCurvature, bool reversed, bool visible) :
            Curve(visible),
            s(length),
            sigma_2(sharpness / 2),
            kappa0(initialCurvature),
            theta0(initialHeading),
            p0(initialPosition),
            reversed(reversed) {}

    Vector2 Clothoid::get_point(double t) const {
        auto scale = sqrt(this->sigma_2 / M_PI_2);
        if (kappa0 == 0 && t * scale <= 1) {
            // use fresnel table
            t *= scale;

            auto lerpTime = t * FRESNEL_TABLE_SIZE;
            auto index = (int) lerpTime;
            lerpTime -= index;

            if (index + 1 < FRESNEL_TABLE_SIZE) {
                return this->p0 + lerp<double, Vector2>(FRESNEL_TABLE[index], FRESNEL_TABLE[index + 1],
                                                                lerpTime).rotate(this->theta0) / scale;
            }
            return this->p0 + scale * FRESNEL_TABLE[index].rotate(this->theta0);
        }

        return this->p0 + integral<double, Vector2>(
                    [this](double x) -> Vector2 {
                        return {std::cos(this->sigma_2 * x * x + this->kappa0 * x + this->theta0),
                                std::sin(this->sigma_2 * x * x + this->kappa0 * x + this->theta0)};
                    }, 0, this->s, std::max((int)(this->s * 10), 10));
    }

    void Clothoid::get_waypoints(std::vector<path::Vector2>& output, int numWaypoints) const {
        auto sz = (long)output.size();
        if (kappa0 == 0) {
            // a slight optimization
            moving_integral<double, Vector2>(
                    output,
                    [this](double x) -> Vector2 {
                        return {
                                std::cos(this->sigma_2 * x * x + this->theta0),
                                std::sin(this->sigma_2 * x * x + this->theta0)
                        };
                    }, 0, this->s, numWaypoints, this->p0);
        } else {
            moving_integral<double, Vector2>(
                    output,
                    [this](double x) -> Vector2 {
                        return {
                                std::cos(this->sigma_2 * x * x + this->kappa0 * x + this->theta0),
                                std::sin(this->sigma_2 * x * x + this->kappa0 * x + this->theta0)
                        };
                    }, 0, this->s, numWaypoints, this->p0);
        }

        if (this->reversed)
            std::reverse(output.begin() + sz, output.end());
    }

    void
    Clothoid::get_waypoints_spaced(std::vector<Vector2>& output, double ds) const {
        auto sz = (long)output.size();

        if (kappa0 == 0) {
            // a slight optimization
            moving_integral_spaced<double, Vector2>(
                    output,
                    [this](double x) -> Vector2 {
                        return {
                                std::cos(this->sigma_2 * x * x + this->theta0),
                                std::sin(this->sigma_2 * x * x + this->theta0)
                        };
                    }, 0, this->s, ds, this->p0);
        } else {
            moving_integral_spaced<double, Vector2>(
                    output,
                    [this](double x) -> Vector2 {
                        return {
                                std::cos(this->sigma_2 * x * x + this->kappa0 * x + this->theta0),
                                std::sin(this->sigma_2 * x * x + this->kappa0 * x + this->theta0)
                        };
                    }, 0, this->s, ds, this->p0);
        }

        if (this->reversed)
            std::reverse(output.begin() + sz, output.end());
    }

    double Clothoid::get_initial_curvature() const {
        return this->kappa0;
    }

    double Clothoid::get_initial_heading() const {
        return this->theta0;
    }

    double Clothoid::get_length() const {
        return this->s;
    }

    double Clothoid::get_sharpness() const {
        return this->sigma_2 * 2;
    }

    Vector2 Clothoid::get_initial_position() const {
        return this->p0;
    }

    void Clothoid::set_initial_curvature(double curvature) {
        this->kappa0 = curvature;
    }

    void Clothoid::set_initial_heading(double heading) {
        this->theta0 = heading;
    }

    void Clothoid::set_length(double length) {
        this->s = length;
    }

    void Clothoid::set_sharpness(double sharpness) {
        this->sigma_2 = sharpness / 2;
    }

    void Clothoid::set_initial_position(path::Vector2 position) {
        this->p0 = position;
    }

    void Clothoid::configure(path::Vector2 initialPosition, double initialHeading, double length, double sharpness,
                             double initialCurvature, bool reversed) {
        this->s = length;
        this->p0 = initialPosition;
        this->theta0 = initialHeading;
        this->sigma_2 = sharpness / 2;
        this->kappa0 = initialCurvature;
        this->reversed = reversed;
    }
} // namespace path