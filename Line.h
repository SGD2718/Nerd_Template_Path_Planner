//
// Created by Benjamin Lee on 8/18/24.
//

#ifndef VEX_PATH_PLANNER_LINE_H
#define VEX_PATH_PLANNER_LINE_H

#include "Curve.h"

namespace path {

    class Line: Curve {
    public:
        Line(Vector2 start, Vector2 end, bool visible = true);

        /**
         * get point at length s
         * @param s
         * @return a point on the line
         */
        [[nodiscard]] Vector2 get_point(double s) const override;

        /**
         * @param numWaypoints number of waypoints
         * @return list of waypoints
         */
        [[nodiscard]] std::vector<path::Vector2> get_waypoints(int numWaypoints) const override;

        /**
         * @param ds step size
         * @return list of waypoints
         */
        [[nodiscard]] std::vector<path::Vector2> get_waypoints_spaced(double ds) const override;

        [[nodiscard]] Vector2 get_start() const;
        [[nodiscard]] Vector2 get_end() const;

        void set_start(Vector2 pos);
        void set_end(Vector2 pos);
        void configure(Vector2 a, Vector2 b);
    private:
        Vector2 start;
        Vector2 end;
    };

} // path

#endif //VEX_PATH_PLANNER_LINE_H
