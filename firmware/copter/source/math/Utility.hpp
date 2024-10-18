#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Point.hpp"
#include "Sphere.hpp"

namespace copter::math
{

bool ComputeIntersection(const Sphere& first, const Sphere& second);

math::Point ComputeNearestPoint(const math::Point& target_point, const math::Sphere& sphere);
math::Point ComputeNearestPoint(const math::Sphere& sphere, const math::Point& target_point);

} // namespace copter::math

#endif