#ifndef MATERIAL_EXPRESSION_HPP
#define MATERIAL_EXPRESSION_HPP

#include "IRayHittable.hpp"
#include "ray_3d.hpp"

namespace rte
{
    class IMaterialExpression
    {
    public:
        virtual ~IMaterialExpression() = default;

        virtual bool scatter(const Ray3D& ray_in, const HitResult& hit_result, Colour& attenuation, Ray3D& scattered_ray) const
        {
            return false;
        }
    };
}
#endif