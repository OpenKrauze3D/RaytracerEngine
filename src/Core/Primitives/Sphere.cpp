#include "Sphere.hpp"

#include "Core/IMaterialExpression.hpp"

rte::Sphere::Sphere(const Point3D& _centre, double _radius, std::shared_ptr<IMaterialExpression> mat)
    : centre(_centre), radius(_radius), material(mat) {}

bool rte::Sphere::hit(const Ray3D& r, interval ray_t, HitResult& rec) const
{
    {
        vec3 oc = centre - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (root <= ray_t.min || ray_t.max <= root) {
            root = (h + sqrtd) / a;
            if (root <= ray_t.min || ray_t.max <= root)
                return false;
        }

        rec.t = root;
        rec.HitLocation = r.at(rec.t);
        vec3 outward_normal = (rec.HitLocation - centre) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.material = material;

        return true;
    }
}
