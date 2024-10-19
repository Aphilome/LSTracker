#include "Sphere.hpp"

namespace copter::math
{

bool Sphere::IsIntersected(const Sphere& other) const
{
    auto distance = center.GetDistance(other.center);
    return (radius + other.radius) >= distance;
}

} // namespace copter::math
