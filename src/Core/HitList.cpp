#include "HitList.hpp"

void rte::HitList::add(std::shared_ptr<IRayHittable> object)
{
    objects.push_back(object);
}

void rte::HitList::clear()
{
    objects.clear();
}

bool rte::HitList::hit(const Ray3D& r, interval ray_t, HitResult& rec) const
{
    HitResult result;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const auto& object : objects)
    {
        if (object->hit(r, interval(ray_t.min, closest_so_far), result))
        {
            hit_anything = true;
            closest_so_far = result.t;
            rec = result;
        }
    }

    return hit_anything;
}
