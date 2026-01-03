#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Image.hpp"
#include "ray_3d.hpp"
#include "rt_minimal.hpp"

namespace rte
{
    struct Camera
    {
        struct Viewport
        {
            Viewport() = default;
            Viewport(const double _height, const Image& img)
            {
                const ImageSpec& spec = img.GetSpec();
                img_aspect_ratio = spec.AspectRatio();
                height = _height;
                width = height * img_aspect_ratio;
                u_coord = vec3(width, 0, 0);
                v_coord = vec3(0, -height, 0);
                pixel_delta_u = u_coord / static_cast<double>(spec.width);
                pixel_delta_v = v_coord / static_cast<double>(spec.height);
            }

            constexpr void coord_upper_left_pixel(const Camera* const camera)
            {
                vec3 viewport_upper_left = camera->centre
                    - vec3(0, 0, camera->focal_length) - u_coord/2 - v_coord/2;
                pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
            }
        
            double width = 0;
            double height = 0;
            double img_aspect_ratio = 0;
            vec3 u_coord;
            vec3 v_coord;
            vec3 pixel_delta_u;
            vec3 pixel_delta_v;
            vec3 pixel00_loc;
        };
        
        Camera() = default;
        Camera(const Point3D& _centre, const Point3D& _up, const Point3D& _right, const Viewport& vp) :
            centre(_centre), up(_up), right(_right), viewport(vp)
        {
            viewport.coord_upper_left_pixel(this);
        }

        Ray3D get_ray(size_t i, size_t j) const;
        vec3 sample_square() const;
        
        Viewport viewport{};
        double focal_length = 1.0;
        Point3D centre = Point3D(0, 0, 0);
        Point3D up = Point3D(0, 1, 0);
        Point3D right = Point3D(1, 0, 0);
    };
}

#endif // !CAMERA_HPP