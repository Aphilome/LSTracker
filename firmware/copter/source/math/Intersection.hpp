#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "Sphere.hpp"

namespace copter::math
{

bool IsIntersected(const Sphere& first, const Sphere& second);

bool ComputeIntersection(const Sphere& first, const Sphere& second);

} // namespace copter::math

#endif
