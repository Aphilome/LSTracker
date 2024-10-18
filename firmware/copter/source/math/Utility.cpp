#include "Utility.hpp"

#include <cmath>

namespace copter::math
{

float ComputeDistance(const Point& first, const Point& second)
{
    auto dx = first.x - second.x;
    auto dy = first.y - second.y;
    auto dz = first.z - second.z;
    return std::sqrt(dx * dx + dy * dy + dz *dz);
}

} // namespace copter::math
