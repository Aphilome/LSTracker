#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Point.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

#include <optional>

namespace copter::math
{

struct SphereIntersectionResult
{
    Point center = {};
    Vector normal = {};
    double radius = {};
};

// Finds intersection of two spheres and returns:
// std::nullopt - no intersection
// radius == 0 - one intersection
// radius > 0 - circle
std::optional<SphereIntersectionResult> ComputeSpheresIntersection(const Sphere& first, const Sphere& second);

// Finds nearest intersection of a line that passes through the center of the sphere and a target point with sphere.
// Use reverse == true to get second point.
math::Point ComputeLineIntersection(const math::Point& target_point, const math::Sphere& sphere, bool reverse);

// The area of the triangle Heron's formula.
double ComputeTriangleArea(double a, double b, double c);

} // namespace copter::math

#endif