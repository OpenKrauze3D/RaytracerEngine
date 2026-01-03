#ifndef VEC4_HPP
#define VEC4_HPP

#include <cmath>
#include <iostream>

#include "vec3.hpp"

namespace rte
{
    struct vec4 {
        
        double e[4]{0,0,0,0};


        constexpr vec4() {}
        constexpr vec4(const vec3& v1, const double e3) : e{v1.x, v1.y, v1.z, e3} {}
        constexpr vec4(const double e3, const vec3& v1) : e{e3, v1.x, v1.y, v1.z} {}
        constexpr vec4(double e0, double e1, double e2, double e3) : e{e0, e1, e2, e3} {}
        constexpr vec4(const vec4& v1) : e{v1[0], v1[1], v1[2], v1[3]} {}

        constexpr vec4 operator-() const { return vec4(-e[0], -e[1], -e[2], e[3]); }
        constexpr double operator[](int i) const { return e[i]; }
        constexpr double& operator[](int i) { return e[i]; }

        constexpr vec4& operator+=(const vec4& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            e[3] += v.e[3];
            return *this;
        }

        constexpr vec4& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            e[3] *= t;
            return *this;
        }

        constexpr vec4& operator/=(double t) {
            return *this *= 1/t;
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        constexpr double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        constexpr Point3D from_homogenous_coords() const {
            return Point3D(e[0]/e[3], e[1]/e[3], e[2]/e[3]);
        }
    };

    // Vector Utility Functions
    inline std::ostream& operator<<(std::ostream& out, const vec4& v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
    }

    constexpr inline vec4 operator+(const vec4& u, const vec4& v) {
        return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
    }

    constexpr inline vec4 operator-(const vec4& u, const vec4& v) {
        return vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
    }

    constexpr inline vec4 operator*(const vec4& u, const vec4& v) {
        return vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
    }

    constexpr inline vec4 operator*(double t, const vec4& v) {
        return vec4(t*v.e[0], t*v.e[1], t*v.e[2], t*v.e[3]);
    }

    constexpr inline vec4 operator*(const vec4& v, double t) {
        return t * v;
    }

    constexpr inline vec4 operator/(const vec4& v, double t) {
        return (1/t) * v;
    }

    constexpr inline double dot(const vec4& u, const vec4& v) {
        return u.e[0] * v.e[0]
             + u.e[1] * v.e[1]
             + u.e[2] * v.e[2]
             + u.e[3] * v.e[3];
    }

    constexpr inline vec4 unit_vector(const vec4& v) {
        return v / v.length();
    }
};

#endif