#ifndef HIT_LIST_HPP
#define HIT_LIST_HPP

#include <vector>
#include <memory>

#include "rt_minimal.hpp"
#include "IRayHittable.hpp"

namespace rte
{
    class HitList : public IRayHittable
    {
    public:
        HitList() = default;
        HitList(std::shared_ptr<IRayHittable> object) { add(object); }

        void add(std::shared_ptr<IRayHittable> object);
        void clear();

        bool hit(const Ray3D& r, interval ray_t, HitResult& rec) const override;

        
    public:
        std::vector<std::shared_ptr<IRayHittable>> objects;
    };
}

#endif //!HIT_LIST