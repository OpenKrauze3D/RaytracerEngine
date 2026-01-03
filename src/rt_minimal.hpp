#ifndef RT_MINIMAL_HPP
#define RT_MINIMAL_HPP

// Common Headers
#include <cmath>
#include <limits>
#include <random>

// Constants
namespace rte
{
    
    constexpr double DINFINITY = std::numeric_limits<double>::infinity();
    constexpr double PI = 3.1415926535897932385;
    constexpr double PI2 = PI * 2;
    constexpr double H_PI = PI/2;

    // Utility Functions
    constexpr double degrees_to_radians(double degrees) {
        return degrees * PI / 180.0;
    }

    inline double random_double()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator(0);
        return distribution(generator);
    }
    
    inline double random_double(double min, double max)
    {
        return min + (max - min) * random_double();
    }
}

#endif