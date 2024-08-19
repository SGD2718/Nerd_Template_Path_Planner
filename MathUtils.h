//
// Created by Benjamin Lee on 8/15/24.
//

#ifndef VEX_PATH_PLANNER_MATHUTILS_H
#define VEX_PATH_PLANNER_MATHUTILS_H

#include <functional>
#include <cassert>
#include "Vector2.h"
#include <iostream>

namespace math {
    /**
     * @brief approximate integral using Simpson's Rule.
     * @tparam I input type, also used for integration bounds
     * @tparam O (optional) output type
     * @param f integrand
     * @param a lower limit of integration
     * @param b upper limit of integration
     * @param steps number of steps
     * @return integral value
     */
    template <typename I, typename O>
    O integral(std::function<O(I)> f, I a, I b, int steps) {
        steps *= 2;
        I dx = (b - a) / steps;
        O sum = f(a);

        for (int i = 1; i < steps-1; i += 2)
            sum += f(a + i * dx) * 4 + f(a + (i + 1) * dx) * 2;
        sum += f(b - dx) * 4 + f(b);

        return dx / 3 * sum;
    }

    /**
     * @brief approximate integral on all ranges [a, a], [a, a+dx], [a + 2dx], ..., up to [a, b] using Simpson's Rule.
     * @tparam I input type, also used for integration bounds
     * @tparam O (optional) output type
     * @param f integrand
     * @param a lower limit of integration
     * @param b upper limit of integration
     * @param steps number of steps
     * @param start (optional) used as the initial sum before computing the integral
     * @return a list of integral results for each sub-interval
     */
    template <typename I, typename O>
    std::vector<O> moving_integral(std::function<O(I)> f, I a, I b, int steps, O start = O()) {
        O next = f(a); // used to avoid needing to recompute f(x)

        O sum = start;
        std::vector<O> sums = {sum};
        sums.reserve(steps);

        steps *= 2;
        I dx = (b - a) / (steps - 2);
        I dx_3 = dx / 3;

        sum /= dx_3;

        for (int i = 1; i < steps - 1; ++i) {
            sum += next + f(a + i * dx) * 4;
            next = f(a + (++i) * dx);
            sum += next;
            sums.emplace_back(sum * dx_3);
        }

        return sums;
    }

    /**
     * @brief approximate integral on all ranges [a, a], [a, a+dx], [a + 2dx], ..., up to [a, b] using Simpson's Rule.
     * @tparam I input type, also used for integration bounds
     * @tparam O (optional) output type
     * @param f integrand
     * @param a lower limit of integration
     * @param b upper limit of integration
     * @param dx number of steps
     * @param start (optional) used as the initial sum before computing the integral
     * @return a list of integral results for each sub-interval
     */
    template <typename I, typename O>
    std::vector<O> moving_integral_spaced(std::function<O(I)> f, I a, I b, I dx, O start = O()) {
        O next = f(a); // used to avoid needing to recompute f(x)

        int steps = ( (b - a) / fabs(dx) ) * 2;
        bool useEnd = fabs(dx * steps - b) > 0.001;

        dx /= 2;
        I dx_3 = dx / 3;

        O sum = start / dx_3;
        std::vector<O> sums = {start};
        sums.reserve(steps / 2 + useEnd + 1);

        for (int i = 1; i < steps; ++i) {
            sum += next + f(a + i * dx) * 4;
            next = f(a + (++i) * dx);
            sum += next;
            sums.emplace_back(sum * dx_3);
        }

        if (useEnd) {
            // use a smaller window for the last point
            sum *= dx_3;
            dx = (b - steps * dx) / 2;
            sum += (next + f(b - dx) * 4 + f(b)) * dx / 3;
            sums.emplace_back(sum);
        }

        return sums;
    }

    /**
     * @brief linear interpolation between a and b at time t
     * @tparam I (optional) type of time parameter
     * @tparam O type of a and b
     * @param a start
     * @param b end
     * @param t time parameter
     * @return interpolation of a and b at time t.
     */
    template <typename I, typename O=I> O lerp(O a, O b, I t) {
        return a + (b-a) * t;
    }

    /**
     * @brief maps an interval with a function
     * @tparam I input type
     * @tparam O output type
     * @param f function
     * @param a start x
     * @param b end x
     * @param dx step size
     * @return function output on the interval
     */
    template <typename I, typename O = I> std::vector<O> map_interval_spaced(std::function<O(I)> f, I a, I b, I dx) {
        if (b < a)
            dx = -dx;

        int steps = (b - a) / fabs(dx);
        bool useEnd = fabs(dx * steps - b) > 0.001;

        std::vector<O> res;
        res.reserve(steps + useEnd + 1);

        for (int i = 0; i <= steps; ++i)
            res.emplace_back(f(a + dx * i));

        if (useEnd)
            res.emplace_back(f(b));

        return res;
    }

    /**
     * @brief maps an interval with a function
     * @tparam I input type
     * @tparam O output type
     * @param f function
     * @param a start x
     * @param b end x
     * @param steps number of points evaluated
     * @return function output on the interval
     */
    template <typename I, typename O = I> std::vector<O> map_interval(std::function<O(I)> f, I a, I b, int steps) {
        std::vector<O> res;
        res.reserve(steps);
        I dx = (b - a) / (steps - 1);

        for (int i = 0; i < steps; ++i)
            res.emplace_back(f(a + dx * i));

        return res;
    }

} // math

#endif //VEX_PATH_PLANNER_MATHUTILS_H
