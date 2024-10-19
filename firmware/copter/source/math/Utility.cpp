#include "Utility.hpp"
#include "Vector.hpp"

#include <cmath>

namespace copter::math
{

std::optional<SphereIntersectionResult> ComputeIntersection(const Sphere& first, const Sphere& second)
{
    if (!first.IsIntersected(second))
        return std::nullopt;

    auto distance = first.center.GetDistance(second.center);
    auto area = ComputeTriangleArea(first.radius, second.radius, distance);
    auto height = 2.0 * area / distance; // distance * height / 2 = area

    auto circle_dir = Vector(first.center, second.center);
    circle_dir.Normalize();

    auto circle_radius = height;
    auto circle_distance = std::sqrt(first.radius * first.radius - circle_radius * circle_radius);
    auto circle_center = first.center;
    circle_center.x += circle_dir.x * circle_distance;
    circle_center.y += circle_dir.y * circle_distance;
    circle_center.z += circle_dir.z * circle_distance;
    return SphereIntersectionResult{ circle_center, circle_dir, circle_radius };
}

math::Point ComputeNearestPoint(const math::Point& target_point, const math::Sphere& sphere)
{
    auto radius_dir = Vector(sphere.center, target_point);
    radius_dir.Normalize();
    return {
        sphere.center.x + radius_dir.x * sphere.radius,
        sphere.center.y + radius_dir.y * sphere.radius,
        sphere.center.z + radius_dir.z * sphere.radius
    };
}

math::Point ComputeNearestPoint(const math::Sphere& sphere, const math::Point& target_point)
{
    return ComputeNearestPoint(target_point, sphere);
}

double ComputeTriangleArea(double a, double b, double c)
{
    double p = 0.5 * (a + b + c);
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

} // namespace copter::math
