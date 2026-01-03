#ifndef MATERIALS_SPECULAR_HPP
#define MATERIALS_SPECULAR_HPP

#include "Core/IMaterialExpression.hpp"

namespace rte
{
    class MAT_Specular : public IMaterialExpression
    {
    public:
        MAT_Specular(const Colour& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const Ray3D& ray_in, const HitResult& hit_result, Colour& attenuation, Ray3D& scattered_ray)
        const override {
            vec3 reflected = reflect(ray_in.direction(), hit_result.HitNormal);
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            scattered_ray = Ray3D(hit_result.HitLocation, reflected);
            attenuation = albedo;
            return (dot(scattered_ray.direction(), hit_result.HitNormal) > 0);
        }

    private:
        Colour albedo;
        double fuzz;
    };
}

#endif