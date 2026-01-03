#include "Camera.hpp"

rte::Ray3D rte::Camera::get_ray(size_t i, size_t j) const
{
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    auto offset = sample_square();
    auto pixel_sample = viewport.pixel00_loc
                      + ((i + offset[0]) * viewport.pixel_delta_u)
                      + ((j + offset[1]) * viewport.pixel_delta_v);

    auto ray_origin = centre;
    auto ray_direction = pixel_sample - ray_origin;

    return {ray_origin, ray_direction};
}

rte::vec3 rte::Camera::sample_square() const
{
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square
    return vec3(random_double() - 0.5, random_double() - 0.5,  random_double() - 0.6);
}
