#include "Scene.hpp"

#include <thread>

#include "IMaterialExpression.hpp"
#include "post_processing.hpp"
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

void rte::Scene::save(std::string_view fp, bool fill_alpha, double alpha)
{
    output_image.writeToDisk(fp, fill_alpha, alpha);
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
    std::cout << "Starting..." << std::endl;
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
    }

    std::clog << "\rDone\t\t\t\t";
}

void rte::Scene::multi_core_render()
{
    const ImageSpec& spec = output_image.GetSpec();
    const auto WIDTH = spec.width;
    const auto HEIGHT = spec.height;
    const size_t THREADS = std::thread::hardware_concurrency();
    // const size_t THREADS = 16;
    const size_t ROWS_PER_THREAD = ceil((HEIGHT + THREADS - 1)/THREADS);

    std::cout << "THREADS: " << THREADS << std::endl;
    std::cout << "ROWS_PER_THREAD: " << ROWS_PER_THREAD << std::endl;

    std::vector<std::thread> threads;
    for (size_t i = 0; i < THREADS; ++i)
    {
        size_t yStart = i * ROWS_PER_THREAD;
        size_t yEnd   = std::min(yStart + ROWS_PER_THREAD, HEIGHT);

        if (yStart >= yEnd)
            break;
        
        threads.emplace_back(&Scene::render_job,
            yStart, yEnd, std::cref(spec), samples_per_pixel,
            pixel_samples_scale, max_bounces,  std::cref(camera),  std::cref(world), std::ref(output_image));

    }

    for (auto& t : threads)
        t.join();

    std::clog << "\rDone\t\t\t\t";
}

void rte::Scene::render_job(size_t startY, size_t endY, const ImageSpec& spec, int samples_per_pixel,
    float pixel_sample_scale, int max_bounces, const Camera& camera, const IRayHittable& world, Image& output_image)
{
    printf("%d-ID: interval{%llu,%llu}, samples{%d}\n", std::this_thread::get_id(), startY, endY, samples_per_pixel);
    const auto WIDTH = spec.width;
    const auto HEIGHT = spec.height;
    
    for (size_t i = 0; i < WIDTH; ++i)
    {
        for (size_t j = startY; j < endY; ++j)
        {
            const size_t idx = ((j * WIDTH) + i);
            Colour colour(0,0,0);
            for (int sample = 0; sample < samples_per_pixel; ++sample)
            {
                Ray3D ray = camera.get_ray(i,j);
                colour += ray_colour(ray, max_bounces, world);
            }
            colour = colour * pixel_sample_scale;
            output_image.pixels[idx][0] = colour[0];
            output_image.pixels[idx][1] = colour[1];
            output_image.pixels[idx][2] = colour[2];
        }
    }
}

rte::Colour rte::Scene::ray_colour(const Ray3D& ray, int bounces, const IRayHittable& hittable)
{
    HitResult result{};

    if (bounces <= 0)
    {
        return Colour(0,0,0);
    }
    
    if (hittable.hit(ray, interval(0.0001, DINFINITY), result)) {
        Ray3D scattered;
        Colour attenuation;
        
        if (result.material->scatter(ray, result, attenuation, scattered))
        {
            return attenuation * ray_colour(scattered, bounces - 1, hittable);
        }
    }

    vec3 unit_direction = unit_vector(ray.direction());
    double lerp = 0.5*(unit_direction.y + 1.0);
    return (1.0-lerp)*Colour(1.0, 1.0, 1.0) + lerp*Colour(0.5, 0.7, 1.0);
}
