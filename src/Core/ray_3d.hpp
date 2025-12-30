#ifndef RAY3D_HPP
#define RAY3D_HPP

#include "vec3.hpp"

namespace rte
{
    struct Ray3D {
        
        constexpr Ray3D() {}
        constexpr Ray3D(const Point3D& origin, const vec3& direction) : orig(origin), dir(direction) {}

        constexpr const Point3D& origin() const  { return orig; }
        constexpr const vec3& direction() const { return dir; }

        constexpr Point3D at(double t) const {
            return orig + t*dir;
        }

        Point3D orig = {0,0,0};
        vec3 dir = {0,0,0};
    };

    constexpr bool hit_sphere(const Point3D& center, double radius, const Ray3D& r)
    {
        vec3 oc = center - r.origin();
        auto a = dot(r.direction(), r.direction());
        auto b = -2.0 * dot(r.direction(), oc);
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        return (discriminant >= 0);
    }
    
    constexpr Colour ray_colour(const Ray3D& ray)
    {
        if (hit_sphere({0,0,-1}, 0.5f, ray))
        {
            return Colour(1,0,0);
        }
        vec3 unit_direction = unit_vector(ray.direction());
        const double lerp = 0.5*(unit_direction.y + 1.0);
        return (1.0-lerp)*Colour(1.0, 1.0, 1.0) + lerp*Colour(0.5, 0.7, 1.0);
    }

    
};
#endif