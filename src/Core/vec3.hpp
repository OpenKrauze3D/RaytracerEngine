#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

#include "rt_minimal.hpp"

namespace rte
{
    struct vec3 {
        union
        {
            double e[3] = {0,0,0};
            struct { double x, y, z; };
            // struct { double r, g, b; };
        };

        constexpr vec3() = default;
        constexpr vec3(const double& e0, const double& e1, const double& e2) : e{e0, e1, e2} {}

        constexpr vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        constexpr double operator[](const int i) const { return e[i]; }
        constexpr double& operator[](const int i) { return e[i]; }

        constexpr vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        constexpr vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        constexpr vec3& operator/=(double t) {
            return *this *= 1/t;
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        constexpr double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        static vec3 random()
        {
            return {random_double(), random_double(), random_double()};
        }

        static vec3 random(double min, double max)
        {
            return {random_double(min, max), random_double(min, max), random_double(min, max)};
        }
    };

    // point3 is just an alias for vec3, but useful for geometric clarity in the code.
    using Point3D = vec3;
    using Colour = vec3;


    // Vector Utility Functions
    inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    constexpr inline vec3 operator+(const vec3& u, const vec3& v) {
        return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    constexpr inline vec3 operator-(const vec3& u, const vec3& v) {
        return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    constexpr inline vec3 operator*(const vec3& u, const vec3& v) {
        return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    constexpr inline vec3 operator*(double t, const vec3& v) {
        return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
    }

    constexpr inline vec3 operator*(const vec3& v, double t) {
        return t * v;
    }

    constexpr inline vec3 operator/(const vec3& v, double t) {
        return (1/t) * v;
    }

    constexpr inline double dot(const vec3& u, const vec3& v) {
        return u.e[0] * v.e[0]
             + u.e[1] * v.e[1]
             + u.e[2] * v.e[2];
    }

    constexpr inline vec3 cross(const vec3& u, const vec3& v) {
        return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    constexpr inline vec3 unit_vector(const vec3& v) {
        return v / v.length();
    }

    inline vec3 random_unit_vector()
    {
        while (true)
        {
            auto p = vec3::random(-1, 1);
            auto lensq = p.length_squared();
            if (1e-160 < lensq && lensq <= 1) // Floating-point abstraction leak correction for [±∞,±∞,±∞]
                return p / sqrt(lensq);
        }
    }

    inline vec3 random_on_hemisphere(const vec3& normal)
    {
        vec3 on_unit_sphere =  random_unit_vector();
        if (dot (on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal.
        {
            return on_unit_sphere;
        }
        return on_unit_sphere * -1.0;
    }
}

#endif