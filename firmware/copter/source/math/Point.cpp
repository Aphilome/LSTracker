#include "Point.hpp"
#include "Vector.hpp"

#include <cmath>

namespace copter::math
{

double Point::GetDistance(const Point& other) const
{
    auto dx = x - other.x;
    auto dy = y - other.y;
    auto dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz *dz);
}

Point Point::GetMiddle(const Point& other) const
{
    return { 0.5 * (x + other.x), 0.5 * (y + other.y), 0.5 * (z + other.z) };
}

void Point::Move(const Vector& normal, double distance)
{
    x += normal.x * distance;
    y += normal.y * distance;
    z += normal.z * distance;
}

} // namespace copter::math
