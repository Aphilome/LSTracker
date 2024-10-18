#include "Intersection.hpp"

#include "Utility.cpp"

namespace copter::math
{

bool IsIntersected(const Sphere& first, const Sphere& second)
{
    auto distance = ComputeDistance(first.center, second.center);
    return (first.radius + second.radius) >= distance;
}

} // namespace copter::math
