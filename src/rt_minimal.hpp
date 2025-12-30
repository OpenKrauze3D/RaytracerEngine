#ifndef RT_MINIMAL_HPP
#define RT_MINIMAL_HPP

// Common Headers
#include <cmath>
#include <limits>

#include "Core/vec3.hpp"
#include "Core/ray_3d.hpp"
#include "Core/vec4.hpp"
#include "Core/IRayHittable.hpp"

// Constants
namespace rte
{
    
    constexpr double DINFINITY = std::numeric_limits<double>::infinity();
    constexpr double PI = 3.1415926535897932385;
    constexpr double PI2 = PI * 2;
    constexpr double H_PI = PI/2;

    // Utility Functions
    constexpr double degrees_to_radians(double degrees) {
        return degrees * PI / 180.0;
    }

    inline Colour ray_colour(const Ray3D& ray, const IRayHittable& hittable)
    {
        HitResult result{};

        if (hittable.hit(ray, 0, DINFINITY, result)) {
            return 0.5 * (result.HitNormal + Colour(1,1,1));
        }

        vec3 unit_direction = unit_vector(ray.direction());
        const double lerp = 0.5*(unit_direction.y + 1.0);
        return (1.0-lerp)*Colour(1.0, 1.0, 1.0) + lerp*Colour(0.5, 0.7, 1.0);
    }

}

#endif