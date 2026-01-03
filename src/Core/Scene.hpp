#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "HitList.hpp"
#include "Image.hpp"
#include "IRayHittable.hpp"
#include "vec3.hpp"
#include "ray_3d.hpp"

namespace rte
{
    class Scene
    {
    public:
        Scene();
        Scene(const ImageSpec& img_spec);
        ~Scene();
    public:
        void attach(const std::shared_ptr<IRayHittable>& object);
    public:
        void init();
        void render();
    public:
        Colour ray_colour(const Ray3D& ray, const IRayHittable& hittable);
    private:
        Image output_image;
        Camera camera{};
        HitList world{};
    };
}

#endif