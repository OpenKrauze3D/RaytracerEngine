#include <chrono>
#include <iostream>
#include <thread>

#include "Core/Image.hpp"
#include "Core/Camera.hpp"
#include "Core/HitList.hpp"
#include "Core/Scene.hpp"
#include "Core/Materials/MAT_Dielectric.hpp"
#include "Core/Materials/MAT_Lambertian.hpp"
#include "Core/Materials/MAT_Specular.hpp"
#include "Core/Primitives/Sphere.hpp"

int main()
{
    // Image
    constexpr uint16_t WIDTH = 1200;
    constexpr uint16_t HEIGHT = 800;
    
    {
        rte::ImageSpec spec = rte::ImageSpec(WIDTH, HEIGHT, rte::ImgType::PNG);
        rte::Scene scene(spec);
        scene.samples_per_pixel = 128;
        scene.max_bounces = 16;
        scene.init();

        auto material_ground = std::make_shared<rte::MAT_Lambertian>(rte::Colour(0.8, 0.8, 0.0));
        auto material_center = std::make_shared<rte::MAT_Lambertian>(rte::Colour(0.1, 0.2, 0.5));
        auto material_left   = std::make_shared<rte::MAT_Dielectric>(1.5);
        auto material_bubble   = std::make_shared<rte::MAT_Dielectric>(1.0/1.50);
        auto material_right  = std::make_shared<rte::MAT_Specular>(rte::Colour(0.8, 0.6, 0.2), 0.1);
        
        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D(0,-100.5,-1), 100,  material_ground));
        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D( 0.0,    0.0, -1.2),   0.5, material_center));
        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D(-1.0,    0.0, -1.0),   0.5, material_left));
        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D(-1.0,    0.0, -1.0),   0.4, material_bubble));
        scene.attach(std::make_shared<rte::Sphere>(rte::Point3D( 1.0,    0.0, -1.0),   0.5, material_right));

        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        scene.multi_core_render();
        
        // scene.render();
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << duration.count() << " ms" << std::endl;
        scene.save("./test", true, 1.0f);
    }
    std::cin.get();

    return 0;
}
