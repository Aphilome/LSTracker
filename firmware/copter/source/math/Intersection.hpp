#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

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

// Finds intersection of sphere and plane, returns:
// std::nullopt - no intersection
// radius == 0 - one intersection
// radius > 0 - circle
std::optional<SphereIntersectionResult> ComputeSphereAndPlaneIntersection(const Sphere& sphere, const Point& plane_point, const Vector& plane_normal);

// Finds nearest intersection of a line that passes through the center of the sphere and a target point with sphere.
// Use nearest == false to get second point.
math::Point ComputeLineIntersection(const math::Point& target_point, const math::Sphere& sphere, bool nearest = true);

} // namespace copter::math

#endif