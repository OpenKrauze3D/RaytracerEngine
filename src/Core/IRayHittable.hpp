#ifndef IRAY_HITTABLE_HPP
#define IRAY_HITTABLE_HPP

#include "vec3.hpp"
#include "ray_3d.hpp"

namespace rte
{
    struct HitResult {
        Point3D HitLocation;
        vec3 HitNormal;
        double t;
        bool front_face;

        void set_face_normal(const Ray3D& ray, const vec3& outward_normal) {
            // Sets the hit record normal vector.
            // NOTE: the parameter `outward_normal` is assumed to have unit length.
            front_face = dot(ray.dir, outward_normal) < 0;
            HitNormal = front_face ? outward_normal : -outward_normal;
        }
    };

    class IRayHittable
    {
    public:
        virtual ~IRayHittable() = default;
        virtual bool hit(const Ray3D& r, double ray_tmin, double ray_tmax, HitResult& rec) const = 0;
    };
}

#endif