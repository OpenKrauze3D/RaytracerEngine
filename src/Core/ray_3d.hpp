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

    constexpr double hit_sphere(const Point3D& center, double radius, const Ray3D& r)
    {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = h*h - a*c;
        // return (discriminant >= 0);
        
        if (discriminant < 0) {
            return -1.0;
        } else {
            return (h - std::sqrt(discriminant) ) / a;
        }
    }
    
    constexpr Colour ray_colour(const Ray3D& ray)
    {
        double t = hit_sphere(Point3D(0.2,-0.5,-1), 0.5, ray);
        if (t > 0.0) {
            vec3 N = unit_vector(ray.at(t) - vec3(0,0,-1));
            return 0.5 * Point3D(N.x+1, N.y+1, N.z+1);
        }
        
        vec3 unit_direction = unit_vector(ray.direction());
        const double lerp = 0.5*(unit_direction.y + 1.0);
        return (1.0-lerp)*Colour(1.0, 1.0, 1.0) + lerp*Colour(0.5, 0.7, 1.0);
    }

    
};
#endif