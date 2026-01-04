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
            
            void init(const Camera* const camera)
            {
                const ImageSpec& spec = camera->img_spec;
                img_aspect_ratio = spec.AspectRatio();                
                const double theta = degrees_to_radians(camera->vfov);
                const double h = std::tan(theta/2.0);
                height = 2.0 * h * camera->focus_dist;
                width = height * img_aspect_ratio;

                u_coord = width * camera->u;
                v_coord = height * -camera->v;

                pixel_delta_u = u_coord / static_cast<double>(spec.width);
                pixel_delta_v = v_coord / static_cast<double>(spec.height);
            }

            constexpr void coord_upper_left_pixel(const Camera* const camera)
            {
                vec3 viewport_upper_left = camera->centre - (camera->focus_dist * camera->w)- u_coord/2 - v_coord/2;
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
        
        void init();
        void set_location(vec3 location);
        void update_projection();
        
        Ray3D get_ray(size_t i, size_t j) const;
        vec3 sample_square() const;
        
        // Returns a random point in the camera defocus disk.
        Point3D defocus_disk_sample() const;
        
        Viewport viewport{};

        
        Point3D centre = Point3D(0, 0, 0);
        Point3D up = Point3D(0, 1, 0);
        Point3D right = Point3D(1, 0, 0);

        Point3D lookat  = Point3D(0,0,-1);  // Point camera is looking at
        vec3   u, v, w;                     // Camera frame basis vectors
        
        double focal_length = 1.0;
        double vfov     = 90;               // Vertical view angle (field of view)
        
        double defocus_angle = 0;  // Variation angle of rays through each pixel
        double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus
        vec3   defocus_disk_u;       // Defocus disk horizontal radius
        vec3   defocus_disk_v;       // Defocus disk vertical radius
        
        ImageSpec img_spec;
    };
}

#endif // !CAMERA_HPP