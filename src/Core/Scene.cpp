#include "Scene.hpp"

#include "IMaterialExpression.hpp"
#include "rt_minimal.hpp"


rte::Scene::Scene()
{
}

rte::Scene::Scene(const ImageSpec& img_spec)
{
    output_image = Image(img_spec);
}

rte::Scene::~Scene() {}

void rte::Scene::attach(const std::shared_ptr<IRayHittable>& object)
{
    world.add(object);
}

void rte::Scene::init()
{
    camera.centre = {0,0.2,0.3};
    camera.viewport = Camera::Viewport(1.5f, output_image);
    camera.viewport.coord_upper_left_pixel(&camera);
    pixel_samples_scale = 1.0 / static_cast<double>(samples_per_pixel);
}


void rte::Scene::render()
{
    const ImageSpec& spec = output_image.GetSpec();
    const auto WIDTH = spec.width;
    const auto HEIGHT = spec.height;
    
    for (size_t i = 0; i < WIDTH; ++i)
    {
        for (size_t j = 0; j < HEIGHT; ++j)
        {
            const size_t idx = ((j * WIDTH) + i);
            Colour colour(0,0,0);
            for (int sample = 0; sample < samples_per_pixel; ++sample)
            {
                Ray3D ray = camera.get_ray(i,j);
                colour += ray_colour(ray, max_bounces, world);
            }
            colour = colour * pixel_samples_scale;
            output_image.pixels[idx][0] = colour[0];
            output_image.pixels[idx][1] = colour[1];
            output_image.pixels[idx][2] = colour[2];
        }
        std::clog << "\rScanlines remaining: " << (WIDTH - i);
    }

    std::clog << "\r\r\r" << std::endl;
    output_image.writeToDisk("./test", true);
    std::clog << "\rDone\t\t\t\t";
    std::cin.get();
}


rte::Colour rte::Scene::ray_colour(const Ray3D& ray, int depth, const IRayHittable& hittable)
{
    HitResult result{};

    if (depth <= 0)
    {
        return Colour(0,0,0);
    }
    
    if (hittable.hit(ray, interval(0.0001, DINFINITY), result)) {
        Ray3D scattered;
        Colour attenuation;
        if (result.material->scatter(ray, result, attenuation, scattered))
        {
            return attenuation * ray_colour(scattered, depth - 1, hittable);
        }
        return Colour(0,0,0);
        // vec3 direction = result.HitNormal + random_unit_vector();
        // return 0.5 * ray_colour(Ray3D(result.HitLocation, direction), depth-1, hittable);
    }

    vec3 unit_direction = unit_vector(ray.direction());
    double lerp = 0.5*(unit_direction.y + 1.0);
    return (1.0-lerp)*Colour(1.0, 1.0, 1.0) + lerp*Colour(0.5, 0.7, 1.0);
}
