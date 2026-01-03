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
        explicit Scene(const ImageSpec& img_spec);
        ~Scene();
    public:
        void attach(const std::shared_ptr<IRayHittable>& object);
    public:
        void init();
        void render();
    public:
        Colour ray_colour(const Ray3D& ray, int depth, const IRayHittable& hittable);
    public:
        int samples_per_pixel = 10;
        int max_bounces = 10;
    private:
        double pixel_samples_scale = 1.0f;
        Image output_image;
        Camera camera{};
        HitList world{};
    };
}

#endif