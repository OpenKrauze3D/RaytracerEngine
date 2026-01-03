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
        rte::Scene scene(spec); 
        scene.init();

        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D(-1,0,-1), 0.3));
        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D(0,-100.5,-1), 100));

        scene.render();
    }
    std::cin.get();

    return 0;
}
