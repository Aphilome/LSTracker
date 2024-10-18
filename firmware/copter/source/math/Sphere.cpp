#include "Sphere.hpp"

namespace copter::math
{

bool Sphere::IsIntersected(const Sphere& first, const Sphere& second) const
{
    auto distance = first.center.GetDistance(second.center);
    return (first.radius + second.radius) >= distance;
}

} // namespace copter::math
