#ifndef RT_MINIMAL_HPP
#define RT_MINIMAL_HPP

// Common Headers
#include <cmath>
#include <limits>

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
}

#endif