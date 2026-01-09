#include <chrono>
#include <iostream>
#include <thread>

#include "Core/Image.hpp"
#include "Core/Camera.hpp"
#include "Core/HitList.hpp"
#include "Core/Scene.hpp"
#include "Core/Materials/MAT_Transmissive.hpp"
#include "Core/Materials/MAT_Lambertian.hpp"
#include "Core/Materials/MAT_Specular.hpp"
#include "Core/Primitives/Sphere.hpp"

constexpr uint16_t WIDTH = 1280;
constexpr uint16_t HEIGHT = 720;

int main()
{
    using namespace rte;
    
    ImageSpec spec = ImageSpec(WIDTH, HEIGHT, ImgType::PNG);
    Scene scene(spec);
    scene.samples_per_pixel = 512;
    scene.max_bounces = 32;
    scene.init();

    
    auto ground_material = std::make_shared<MAT_Lambertian>(Colour(0.5, 0.5, 0.5));
    scene.attach(std::make_shared<Sphere>(Point3D(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3D center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3D(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<IMaterialExpression> sphere_material;

                if (choose_mat < 0.5) {
                    // diffuse
                    auto albedo = Colour::random() * Colour::random();
                    sphere_material = std::make_shared<MAT_Lambertian>(albedo);
                    scene.attach(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.55) {
                    // metal
                    auto albedo = Colour::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<MAT_Specular>(albedo, fuzz);
                    scene.attach(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    auto absorption = Colour::random(0.001, 0.9);
                    sphere_material = std::make_shared<MAT_Transmissive>(1-absorption, 1.5);
                    scene.attach(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<MAT_Transmissive>(Colour(0.05,1,1),4.22);
    scene.attach(std::make_shared<Sphere>(Point3D(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<MAT_Lambertian>(Colour(0.4, 0.2, 0.1));
    scene.attach(std::make_shared<Sphere>(Point3D(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<MAT_Specular>(Colour(0.7, 0.6, 0.5), 0.0);
    scene.attach(std::make_shared<Sphere>(Point3D(4, 1, 0), 1.0, material3));

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    scene.multi_core_render();
    
    // scene.render();
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << duration.count()/1000.0 << "s\n";
    scene.save("../renders/book1", true, 1.0f);
    
    return 0;
}
