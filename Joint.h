//
// Created by Benjamin Lee on 8/18/24.
//

#ifndef VEX_PATH_PLANNER_JOINT_H
#define VEX_PATH_PLANNER_JOINT_H

#include "Vector2.h"
#include "Clothoid.h"
#include "CircularArc.h"
#include "Line.h"

namespace path {
    class Joint {
    public:
        Joint(Vector2 *pStart, Vector2 *pMiddle, Vector2 *pEnd, double sharpness, double maxCurvature);

        void update();
        std::vector<Vector2> get_waypoints(double ds) const;

    private:
        Vector2* pStart;
        Vector2* pMiddle;
        Vector2* pEnd;

        Vector2 pCurvatureControl;
        Vector2 pSharpnessControl1;
        Vector2 pSharpnessControl2;

        double maxCurvature;
        double sharpness;

        Line line1;
        Clothoid clothoid1;
        CircularArc arc;
        Clothoid clothoid2;
        Line line2;
    };

} // path

#endif //VEX_PATH_PLANNER_JOINT_H
