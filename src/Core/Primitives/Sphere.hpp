#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Core/IRayHittable.hpp"

namespace rte
{
    class Sphere : public IRayHittable
    {
    public:
        Sphere() = delete;
        Sphere(const Point3D& _centre, double _radius) : centre(_centre), radius(std::fmax(0,_radius)) {}
        ~Sphere() override = default;
    public:
        bool hit(const Ray3D& r, double ray_tmin, double ray_tmax, HitResult& rec) const override;

    public:
        Point3D centre;
        double radius;
    };
}

#endif