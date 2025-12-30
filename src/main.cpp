#include <iostream>

#include "Core/Image.hpp"
#include "Core/Camera.hpp"
#include "Core/ray_3d.hpp"

int main()
{
    // Image
    constexpr uint16_t WIDTH = 1280;
    constexpr uint16_t HEIGHT = 720;

    {
        ImageSpec spec = ImageSpec(WIDTH, HEIGHT, 8);
        Image img(spec);
        rte::Camera camera{};
        camera.viewport = rte::Camera::Viewport(2.0f, img);
        camera.viewport.coord_upper_left_pixel(&camera);

        for (int i = 0; i < WIDTH; ++i)
        {
            std::clog << "\rScanlines remaining: " << (WIDTH - i);
            for (int j = 0; j < HEIGHT; ++j)
            {
                const size_t idx = ((j * WIDTH) + i);

                rte::vec3 pixel_center = camera.viewport.pixel00_loc +
                    (i * camera.viewport.pixel_delta_u) +
                    (j * camera.viewport.pixel_delta_v);
                rte::vec3 ray_direction = pixel_center - camera.centre;
                rte::Ray3D r(camera.centre, ray_direction);

                rte::Colour colour = rte::ray_colour(r);
                img.m_data[idx][0] = colour[0];
                img.m_data[idx][1] = colour[1];
                img.m_data[idx][2] = colour[2];
            }
        }
        std::clog << "\r\r\r" << std::endl;
        img.writeToDisk("./test", true);
        std::clog << "\rDone\t\t\t\t";
        std::cin.get();
    }
    std::cin.get();

    return 0;
}
