#ifndef MATERIALS_LAMBERTIAN_HPP
#define MATERIALS_LAMBERTIAN_HPP

#include "Core/IMaterialExpression.hpp"

namespace rte
{
    class MAT_Lambertian : public IMaterialExpression
    {
    public:
        MAT_Lambertian(const Colour& albedo) : albedo(albedo) {}

        bool scatter(const Ray3D& ray_in, const HitResult& hit_result, Colour& attenuation, Ray3D& scattered_ray) const override
        {
            const vec3 scatter_direction = hit_result.HitNormal + random_unit_vector();
            scattered_ray = Ray3D(hit_result.HitLocation, scatter_direction);
            attenuation = albedo;
            return true;
        }
    private:
        Colour albedo;
    };
}

#endif