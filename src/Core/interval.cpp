#include "interval.hpp"

namespace rte
{
    interval interval::empty = interval(+DINFINITY, -DINFINITY);
    interval interval::universe = interval(-DINFINITY, +DINFINITY);
}