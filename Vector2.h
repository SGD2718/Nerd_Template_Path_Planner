//
// Created by Benjamin Lee on 8/15/24.
//

#ifndef VEX_PATH_PLANNER_VECTOR2_H
#define VEX_PATH_PLANNER_VECTOR2_H

#include <cmath>
#include <string>

namespace path {
    class Vector2 {
    public:
        double x;
        double y;

        Vector2() = default;

        Vector2(double x, double y) : x(x), y(y) {}

        [[nodiscard]] std::string str() const;
        [[nodiscard]] std::string latex() const;

        /**
         * @brief |this|
         * @return vector norm (magnitude)
         */
        [[nodiscard]] double norm() const;

        /**
         * @brief |this|^2
         * @return square of vector norm (magnitude)
         */
        [[nodiscard]] double norm_squared() const;

        /**
         * @brief normalize the vector
         * @return unit direction vector
         */
        [[nodiscard]] Vector2 normalize() const;

        /**
         * @brief dot product
         * @param other another vector
         * @return this • other
         */
        [[nodiscard]] double dot(Vector2 other) const;

        /**
         * @brief cross product this x other
         * @param other another vector
         * @return this x other
         */
        [[nodiscard]] double cross(Vector2 other) const;

        /**
         * @brief component of a vector projected onto this
         * @param direction direction vector
         * @return a.comp(b) = comp_b(a)
         */
        [[nodiscard]] double comp(Vector2 direction) const;

        /**
         * @brief project onto a direction vector
         * @param direction direction vector
         * @return a.proj(b) = proj_b(a)
         */
        [[nodiscard]] Vector2 proj(Vector2 direction) const;

        /**
         * @brief orthogonal component of this onto a direction vector (distance from point to line)
         * @param direction direction vector
         * @return distance from the head of this to the line passing through direction vector
         */
        [[nodiscard]] double orthogonal_comp(Vector2 direction) const;

        /**
         * @brief rotate CCW by theta radians about origin
         * @param theta
         * @return rotated vector
         */
        [[nodiscard]] Vector2 rotate(double theta) const;

        /**
         * @brief Get angle between two vectors.
         * @param other another vector
         * @return angle between this and other
         */
        [[nodiscard]] double angle(Vector2 other) const;

        /**
         * @brief get vector heading in radians
         * @return vector heading in radians
         */
        [[nodiscard]] double heading() const;

        /**
         * @brief reflect this vector about an axis
         * @param axis axis of reflection
         * @return reflected vector
         */
        [[nodiscard]] Vector2 reflect_about(Vector2 axis) const;

        Vector2 operator-() const;
        Vector2 operator+() const;
        Vector2 operator+(Vector2 other) const;
        Vector2 operator-(Vector2 other) const;
        Vector2 operator*(Vector2 other) const;
        Vector2 operator*(double other) const;
        Vector2 operator/(Vector2 other) const;
        Vector2 operator/(double other) const;
        Vector2 operator+=(Vector2 other);
        Vector2 operator-=(Vector2 other);
        Vector2 operator*=(Vector2 other);
        Vector2 operator*=(double other);
        Vector2 operator/=(Vector2 other);
        Vector2 operator/=(double other);
    };

    Vector2 operator*(double a, Vector2 b);
} // namespace path

#endif //VEX_PATH_PLANNER_VECTOR2_H
