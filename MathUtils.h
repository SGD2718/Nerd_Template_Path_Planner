//
// Created by Benjamin Lee on 8/15/24.
//

#ifndef VEX_PATH_PLANNER_MATHUTILS_H
#define VEX_PATH_PLANNER_MATHUTILS_H

#include <functional>
#include <cassert>
#include "Vector2.h"
#include <iostream>

namespace path {
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
     * @param output vector to add points to
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
    void moving_integral(std::vector<O>& output, std::function<O(I)> f, I a, I b, int steps, O start = O()) {
        O next = f(a); // used to avoid needing to recompute f(x)

        O sum = start;
        if (output.capacity() - output.size() < steps)
            output.reserve(output.size() + steps);
        output.emplace_back(sum);

        steps *= 2;
        I dx = (b - a) / (steps - 2);
        I dx_3 = dx / 3;

        sum /= dx_3;

        for (int i = 1; i < steps - 1; ++i) {
            sum += next + f(a + i * dx) * 4;
            next = f(a + (++i) * dx);
            sum += next;
            output.emplace_back(sum * dx_3);
        }
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
        std::vector<O> res;
        moving_integral<I, O>(res, f, a, b, steps, start);
        return res;
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
    void moving_integral_spaced(std::vector<O>& output, std::function<O(I)> f, I a, I b, I dx, O start = O()) {
        if (b < a) {
            auto tmp = a;
            a = b;
            b = tmp;
            dx = -dx;
        }
        O next = f(a); // used to avoid needing to recompute f(x)
        int steps = ( (b - a) / fabs(dx) ) * 2;
        bool useEnd = fabs(dx * steps - b) > 0.001;

        dx /= 2;
        I dx_3 = dx / 3;

        O sum = start / dx_3;

        auto numAdded = steps / 2 + useEnd + 1;
        if (output.capacity() - output.size() < numAdded)
            output.reserve(output.size() + numAdded);
        output.emplace_back(start);

        for (int i = 1; i < steps; ++i) {
            sum += next + f(a + i * dx) * 4;
            next = f(a + (++i) * dx);
            sum += next;
            output.emplace_back(sum * dx_3);
        }

        if (useEnd) {
            // use a smaller window for the last point
            sum *= dx_3;
            dx = (b - steps * dx) / 2;
            sum += (next + f(b - dx) * 4 + f(b)) * dx / 3;
            output.emplace_back(sum);
        }
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
        std::vector<O> res;
        moving_integral_spaced(res, f, a, b, dx, start);
        return res;
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
    template <typename I, typename O=I>
    O lerp(O a, O b, I t) {
        return a + (b-a) * t;
    }

    /**
     * @brief maps an interval with a function
     * @param output vector to add points to
     * @tparam I input type
     * @tparam O output type
     * @param f function
     * @param a start x
     * @param b end x
     * @param dx step size
     */
    template <typename I, typename O = I>
    void map_interval_spaced(std::vector<O>& output, std::function<O(I)> f, I a, I b, I dx) {
        if (b < a)
            dx = -dx;

        int steps = (b - a) / dx; // any negatives should cancel out
        bool useEnd = fabs(dx * steps - b) > 0.001;

        if (output.capacity() - output.size() < steps + useEnd + 1)
            output.reserve(output.size() + steps + useEnd + 1);

        for (int i = 0; i <= steps; ++i)
            output.emplace_back(f(a + dx * i));

        if (useEnd)
            output.emplace_back(f(b));
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
    template <typename I, typename O = I>
    std::vector<O> map_interval_spaced(std::function<O(I)> f, I a, I b, I dx) {
        std::vector<O> output;
        map_interval_spaced<I, O>(output, f, a, b, dx);
        return output;
    }

    /**
     * @brief maps an interval with a function
     * @param output vector to add points to
     * @tparam I input type
     * @tparam O output type
     * @param f function
     * @param a start x
     * @param b end x
     * @param steps number of points evaluated
     */
    template <typename I, typename O = I>
    void map_interval(std::vector<O>& output, std::function<O(I)> f, I a, I b, int steps) {
        if (output.capacity() - output.size() < steps)
            output.reserve(output.size() + steps);
        I dx = (b - a) / (steps - 1);

        for (int i = 0; i < steps; ++i)
            output.emplace_back(f(a + dx * i));
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
    template <typename I, typename O = I>
    std::vector<O> map_interval(std::function<O(I)> f, I a, I b, int steps) {
        std::vector<O> res;
        map_interval<I, O>(res, f, a, b, steps);
        return res;
    }

    template <typename T>
    T sign(T x) {
        return x > 0 ? 1 : x < 0 ? -1 : 0;
    }

} // path

#endif //VEX_PATH_PLANNER_MATHUTILS_H
