#include <iostream>
#include "MathUtils.h"
#include "Vector2.h"
#include "Curves.h"
#include "Fresnel.h"
#include "Joint.h"
#include <chrono>

int main() {
    path::init_fresnel();

    auto v1 = new path::Vector2(0,4);
    auto v2 = new path::Vector2(0,1);
    auto v3 = new path::Vector2(-2,2);
    auto test = path::Joint(v1, v2, v3, 2.75, 2);
    auto c = path::Clothoid({0.472264, 1.416791}, 1.2490457724, 0.727272727273, 2.75);
    auto d = test.get_waypoints(0.1);

    std::cout << "\\left[";
    for (auto &v: d) {
        std::cout << v.latex() << ',';
    }
    std::cout << "\b\\right]\n" << std::endl;
}
