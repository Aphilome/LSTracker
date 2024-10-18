#include "Utility.hpp"

#include <cmath>

namespace copter::math
{

bool ComputeIntersection(const Sphere& first, const Sphere& second)
{
    return false;
}

math::Point ComputeNearestPoint(const math::Point& target_point, const math::Sphere& sphere)
{
    return {};
}

math::Point ComputeNearestPoint(const math::Sphere& sphere, const math::Point& target_point)
{
    return ComputeNearestPoint(target_point, sphere);
}

} // namespace copter::math
