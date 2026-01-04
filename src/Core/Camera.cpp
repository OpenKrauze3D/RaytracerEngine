#include "Camera.hpp"

void rte::Camera::init()
{
    update_projection();
}

void rte::Camera::set_location(vec3 location)
{
    centre = location;
    update_projection();
}

void rte::Camera::update_projection()
{
    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    const vec3 forward_vector = centre - lookat;
    w = unit_vector(forward_vector);
    u = unit_vector(cross(up, w));
    v = cross(w, u);

    // Calculate the camera defocus disk basis vectors.
    double defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
    
    viewport.init(this);
    viewport.coord_upper_left_pixel(this);
}

rte::Ray3D rte::Camera::get_ray(size_t i, size_t j) const
{
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    auto offset = sample_square();
    auto pixel_sample = viewport.pixel00_loc
                      + ((i + offset[0]) * viewport.pixel_delta_u)
                      + ((j + offset[1]) * viewport.pixel_delta_v);

    auto ray_origin = (defocus_angle <= 0) ? centre : defocus_disk_sample();;
    auto ray_direction = pixel_sample - ray_origin;

    return {ray_origin, ray_direction};
}

rte::vec3 rte::Camera::sample_square() const
{
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square
    return vec3(random_double() - 0.5, random_double() - 0.5,  random_double() - 0.6);
}

rte::Point3D rte::Camera::defocus_disk_sample() const
{
    Point3D point = random_in_unit_disk();
    return centre + (point[0] * defocus_disk_u) + (point[1] * defocus_disk_v);
}
