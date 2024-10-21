#include "Sphere.hpp"

namespace copter::math
{

bool Sphere::IsInside(const Sphere& other) const
{
    auto distance = center.GetDistance(other.center);
    return other.radius > (distance + radius);
}

bool Sphere::IsOutside(const Sphere& other) const
{
    auto distance = center.GetDistance(other.center);
    return distance > (radius + other.radius);
}

bool Sphere::IsIntersected(const Sphere& other) const
{
    return !this->IsInside(other)
        && !other.IsInside(*this)
        && !IsOutside(other);
}

} // namespace copter::math
