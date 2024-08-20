//
// Created by Benjamin Lee on 8/18/24.
//

#ifndef VEX_PATH_PLANNER_CIRCULARARC_H
#define VEX_PATH_PLANNER_CIRCULARARC_H

#include "Curve.h"

namespace path {

    class CircularArc: public Curve {
    public:
        explicit CircularArc(Vector2 center = {0, 0}, double startAngle = 0, double endAngle = M_PI * 2, double radius = 1, bool visible = true);

        /**
         * @brief get point on arc
         * @param s theta
         * @return a point on the arc. Note that this does not check if the point is actually on the arc.
         */
        [[nodiscard]] Vector2 get_point(double s) const override;

        /**
         * @brief generate waypoints
         * @param numWaypoints number of waypoints
         * @return list of waypoints
         */
        void get_waypoints(std::vector<path::Vector2>& output, int numWaypoints) const override;

        /**
         * @brief generated waypoints with set spacing
         * @param ds space between waypoints
         * @return list of waypoints
         */
        void get_waypoints_spaced(std::vector<path::Vector2>& output, double ds) const override;

        [[nodiscard]] double get_length() const override;

        [[nodiscard]] Vector2 get_center() const;
        [[nodiscard]] double get_start_angle() const;
        [[nodiscard]] double get_end_angle() const;
        [[nodiscard]] double get_radius() const;

        void set_center(Vector2 pos);
        void set_start_angle(double theta);
        void set_end_angle(double theta);
        void set_radius(double r);
        void configure(Vector2 center, double startAngle, double endAngle, double r);
    private:
        Vector2 center;
        double thetaStart;
        double thetaEnd;
        double radius;
    };

} // path

#endif //VEX_PATH_PLANNER_CIRCULARARC_H
