#include "Point.hpp"

#include <cmath>

namespace copter::math
{

float Point::GetDistance(const Point& other) const
{
    auto dx = x - other.x;
    auto dy = y - other.y;
    auto dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz *dz);
}

Point Point::GetMiddle(const Point& other) const
{
    return { 0.5f * (x + other.x), 0.5f * (y + other.y), 0.5f * (z + other.z) };
}

} // namespace copter::math
