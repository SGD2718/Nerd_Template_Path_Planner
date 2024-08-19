//
// Created by Benjamin Lee on 8/18/24.
//

#include "Vector2.h"

namespace math {
    std::string Vector2::str() const {
        return "(" + std::to_string(x) + "  " + std::to_string(y) + ")";
    }

    std::string Vector2::latex() const {
        return "\\left(" + std::to_string(x) + "," + std::to_string(y) + "\\right)";
    }
    
    double Vector2::norm() const {
        return std::sqrt(x*x + y*y);
    }
    
    double Vector2::norm_squared() const {
        return x*x + y*y;
    }
    
    Vector2 Vector2::normalize() const {
        return *this / this->norm();
    }
    
    double Vector2::dot(Vector2 other) const {
        return this->x * other.x + this->y * other.y;
    }
    
    double Vector2::cross(Vector2 other) const {
        return this->x * other.y - this->y * other.x;
    }
    
    double Vector2::comp(Vector2 direction) const {
        return this->dot(direction) / direction.norm();
    }
    
    Vector2 Vector2::proj(Vector2 direction) const {
        return direction * (this->dot(direction) / direction.norm_squared());
    }
    
    double Vector2::orthogonal_comp(Vector2 direction) const {
        return std::fabs(this->cross(direction) / direction.norm());
    }
    
    Vector2 Vector2::rotate(double theta) const {
        auto c = cos(theta);
        auto s = sin(theta);
        return {(double)(c * this->x - s * this->y), (double)(s * this->x + c * this->y)};
    }

    double Vector2::angle(Vector2 other) const {
        return acos(this->dot(other) / (this->norm() * other.norm()));
    }

    double Vector2::heading() const {
        return atan2(this->y, this->x);
    }

    /**
     * @brief reflect this vector about an axis
     * @param axis axis of reflection
     * @return reflected vector
     */
    Vector2 Vector2::reflect_about(Vector2 axis) const {
        return *this - axis * ( this->dot(axis) * 2 );
    }

    Vector2 Vector2::operator-() const {
        return {-this->x, -this->y};
    }

    Vector2 Vector2::operator+() const {
        return *this;
    }

    Vector2 Vector2::operator+(Vector2 other) const {
        return {this->x + other.x, this->y + other.y};
    }

    Vector2 Vector2::operator-(Vector2 other) const {
        return {this->x - other.x, this->y - other.y};
    }

    Vector2 Vector2::operator*(Vector2 other) const {
        return {this->x * other.x, this->y * other.y};
    }

    Vector2 Vector2::operator*(double other) const {
        return {this->x * other, this->y * other};
    }

    Vector2 Vector2::operator/(Vector2 other) const {
        return {this->x / other.x, this->y / other.y};
    }

    Vector2 Vector2::operator/(double other) const {
        return {this->x / other, this->y / other};
    }

    Vector2 Vector2::operator+=(Vector2 other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector2 Vector2::operator-=(Vector2 other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vector2 Vector2::operator*=(Vector2 other) {
        this->x *= other.x;
        this->y *= other.y;
        return *this;
    }

    Vector2 Vector2::operator*=(double other) {
        this->x *= other;
        this->y *= other;
        return *this;
    }

    Vector2 Vector2::operator/=(Vector2 other) {
        this->x /= other.x;
        this->y /= other.y;
        return *this;
    }

    Vector2 Vector2::operator/=(double other) {
        this->x /= other;
        this->y /= other;
        return *this;
    }

    Vector2 operator*(double a, Vector2 b) {
        return b * a;
    }
}

