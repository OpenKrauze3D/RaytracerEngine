#include <iostream>

#include "Core/Image.hpp"
#include "Core/Camera.hpp"
#include "Core/HitList.hpp"
#include "Core/ray_3d.hpp"
#include "Core/Scene.hpp"
#include "Core/Primitives/Sphere.hpp"

int main()
{
    // Image
    constexpr uint16_t WIDTH = 1280;
    constexpr uint16_t HEIGHT = 720;

    {
        rte::ImageSpec spec = rte::ImageSpec(WIDTH, HEIGHT, rte::ImgType::PNG);
        rte::Scene scene = rte::Scene(spec); 
        scene.init();
        // rte::Image img(spec);
        // rte::Camera camera{};
        // camera.viewport = rte::Camera::Viewport(2.0f, img);
        // camera.viewport.coord_upper_left_pixel(&camera);

        // rte::HitList world{};
        // world.add(std::make_shared<rte::Sphere>(rte::Point3D(-1,0,-1), 0.3));
        // world.add(std::make_shared<rte::Sphere>(rte::Point3D(0,-100.5,-1), 100));

        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D(-1,0,-1), 0.3));
        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D(0,-100.5,-1), 100));
        scene.render();
        // for (int i = 0; i < WIDTH; ++i)
        // {
        //     std::clog << "\rScanlines remaining: " << (WIDTH - i);
        //     for (int j = 0; j < HEIGHT; ++j)
        //     {
        //         const size_t idx = ((j * WIDTH) + i);
        //
        //         rte::vec3 pixel_center = camera.viewport.pixel00_loc +
        //             (i * camera.viewport.pixel_delta_u) +
        //             (j * camera.viewport.pixel_delta_v);
        //         rte::vec3 ray_direction = pixel_center - camera.centre;
        //         rte::Ray3D r(camera.centre, ray_direction);
        //
        //         rte::Colour colour = rte::Scene::ray_colour(r, world);
        //         img.pixels[idx][0] = colour[0];
        //         img.pixels[idx][1] = colour[1];
        //         img.pixels[idx][2] = colour[2];
        //     }
        // }
        // std::clog << "\r\r\r" << std::endl;
        // img.writeToDisk("./test", true);
        // std::clog << "\rDone\t\t\t\t";
        // std::cin.get();
    }
    std::cin.get();

    return 0;
}
