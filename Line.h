//
// Created by Benjamin Lee on 8/18/24.
//

#ifndef VEX_PATH_PLANNER_LINE_H
#define VEX_PATH_PLANNER_LINE_H

#include "Curve.h"

namespace path {

    class Line: public Curve {
    public:
        explicit Line(Vector2 start = {0, 0}, Vector2 end = {0, 0}, bool visible = true);

        /**
         * get point at length s
         * @param s
         * @return a point on the line
         */
        [[nodiscard]] Vector2 get_point(double s) const override;

        /**
         * @param output vector to add points to
         * @param numWaypoints number of waypoints
         * @return list of waypoints
         */
        void get_waypoints(std::vector<path::Vector2>& output, int numWaypoints) const override;

        /**
         * @param output vector to add points to
         * @param ds step size
         * @return list of waypoints
         */
        void get_waypoints_spaced(std::vector<path::Vector2>& output, double ds) const override;

        [[nodiscard]] Vector2 get_start() const;
        [[nodiscard]] Vector2 get_end() const;

        [[nodiscard]] double get_length() const override;

        void set_start(Vector2 pos);
        void set_end(Vector2 pos);
        void configure(Vector2 a, Vector2 b);
    private:
        Vector2 start;
        Vector2 end;
    };

} // path

#endif //VEX_PATH_PLANNER_LINE_H
