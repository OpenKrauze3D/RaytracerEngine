#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "rt_minimal.hpp"

namespace rte
{
    class interval {
    public:
        double min, max;

        constexpr interval() : min(+DINFINITY), max(-DINFINITY) {} // Default interval is empty

        constexpr interval(double min, double max) : min(min), max(max) {}

        constexpr double size() const {
            return max - min;
        }

        constexpr bool contains(double x) const {
            return min <= x && x <= max;
        }

        constexpr bool surrounds(double x) const {
            return min < x && x < max;
        }

        constexpr double clamp(double x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        static interval empty, universe;
    };

    // const interval interval::empty    = interval(+DINFINITY, -DINFINITY);
    // const interval interval::universe = interval(-DINFINITY, +DINFINITY);
}

#endif