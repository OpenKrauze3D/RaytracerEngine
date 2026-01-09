#ifndef MAT_DIELECTRIC_HPP
#define MAT_DIELECTRIC_HPP

#include "Core/IMaterialExpression.hpp"

namespace rte
{
    class MAT_Transmissive : public IMaterialExpression
    {
    public:
        MAT_Transmissive(const Colour& absorption, double IOR) : absorption(absorption), ior(IOR) {}

        bool scatter(const Ray3D& ray_in, const HitResult& hit_result, Colour& attenuation, Ray3D& scattered_ray) const override
        {
            const double ri = hit_result.front_face ? (1.0/ior) : ior;

            vec3 unit_direction = unit_vector(ray_in.direction());
            const double cos_theta = std::fmin(dot(-unit_direction, hit_result.HitNormal), 1.0);
            const double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = ri * sin_theta > 1.0;
            vec3 direction;
            if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            {
                direction = reflect(unit_direction, hit_result.HitNormal);
            }
            else
            {
                direction = refract(unit_direction, hit_result.HitNormal, ri);
            }

            const Colour transmittance = {
                std::exp(-absorption[0] * hit_result.t),
                std::exp(-absorption[1] * hit_result.t),
                std::exp(-absorption[2] * hit_result.t)
            };
            attenuation = attenuation * transmittance;

            scattered_ray = {hit_result.HitLocation, direction};
            return true;
        }
        
    private:
        // Refractive index in vacuum or air, or the ratio of the material's refractive index over
        // the refractive index of the enclosing media
        Colour absorption;
        double ior;

        static double reflectance(double cosine, double refraction_index) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1 - refraction_index) / (1 + refraction_index);
            r0 = r0*r0;
            return r0 + (1-r0)*std::pow((1 - cosine),5);
        }
    };
}

#endif
