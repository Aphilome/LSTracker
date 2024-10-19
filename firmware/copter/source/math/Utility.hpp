#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Point.hpp"
#include "Sphere.hpp"
#include "Vector.cpp"

#include <optional>

namespace copter::math
{

struct SphereIntersectionResult
{
    Point center = {};
    Vector normal = {};
    float radius = {};
};

// Finds intersection of two spheres and returns:
// std::nullopt - no intersection
// radius == 0 - one intersection
// radius > 0 - circle
std::optional<SphereIntersectionResult> ComputeIntersection(const Sphere& first, const Sphere& second);

math::Point ComputeNearestPoint(const math::Point& target_point, const math::Sphere& sphere);
math::Point ComputeNearestPoint(const math::Sphere& sphere, const math::Point& target_point);

float ComputeTriangleArea(float a, float b, float c);

} // namespace copter::math

#endif