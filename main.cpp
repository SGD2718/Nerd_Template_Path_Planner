#include <iostream>
#include "MathUtils.h"
#include "Vector2.h"
#include "Curves.h"
#include "Fresnel.h"
#include <chrono>

int main() {
    path::init_fresnel();

    auto l = path::Line({-0.4, 0}, {-0.44521, 1.34992});
    auto cl = path::Clothoid(1.509375, {-0.44521, 1.34992}, 1.60427663444, 0.32);
    auto c = path::CircularArc({-2.58520313111, 2.03002199319}, 0.39799437015, 1.22274168313, 2.07039337474);
    auto a = c.get_waypoints_spaced(0.1);
    auto b = cl.get_waypoints_spaced(0.1);
    auto d = l.get_waypoints_spaced(0.1);

    std::cout << "\\left[";
    for (auto &v: d) {
        std::cout << v.latex() << ',';
    }
    for (auto &v: b) {
        std::cout << v.latex() << ',';
    }
    for (auto &v: a) {
        std::cout << v.latex() << ',';
    }
    std::cout << "\b\\right]" << std::endl;
}
