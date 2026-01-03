#include "Scene.hpp"

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
    camera.viewport = Camera::Viewport(2.0f, output_image);
    camera.viewport.coord_upper_left_pixel(&camera);
}


void rte::Scene::render()
{
    const ImageSpec& spec = output_image.GetSpec();
    const auto WIDTH = spec.width;
    const auto HEIGHT = spec.height;
    
    for (size_t i = 0; i < WIDTH-1; i++)
    {
        std::clog << "\rScanlines remaining: " << (WIDTH - i);
        for (size_t j = 0; j < HEIGHT-1; j++)
        {
            size_t idx = ((j * WIDTH) + i);

            vec3 pixel_center = camera.viewport.pixel00_loc +
                (i * camera.viewport.pixel_delta_u) +
                (j * camera.viewport.pixel_delta_v);
            vec3 ray_direction = pixel_center - camera.centre;
            Ray3D r(camera.centre, ray_direction);

            Colour colour = ray_colour(r, world);
            output_image.pixels[idx][0] = colour[0];
            output_image.pixels[idx][1] = colour[1];
            output_image.pixels[idx][2] = colour[2];
        }
    }

    std::clog << "\r\r\r" << std::endl;
    output_image.writeToDisk("./test", true);
    std::clog << "\rDone\t\t\t\t";
    std::cin.get();
}


rte::Colour rte::Scene::ray_colour(const Ray3D& ray, const IRayHittable& hittable)
{
    HitResult result{};

    if (hittable.hit(ray, 0, DINFINITY, result)) {
        return 0.5 * (result.HitNormal + Colour(1,1,1));
    }

    vec3 unit_direction = unit_vector(ray.direction());
    const double lerp = 0.5*(unit_direction.y + 1.0);
    return (1.0-lerp)*Colour(1.0, 1.0, 1.0) + lerp*Colour(0.5, 0.7, 1.0);
}
