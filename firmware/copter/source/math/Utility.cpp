#include "Utility.hpp"
#include "Vector.hpp"

#include <cmath>

namespace copter::math
{

std::optional<SphereIntersectionResult> ComputeSpheresIntersection(const Sphere& first, const Sphere& second)
{
    if (!first.IsIntersected(second))
        return std::nullopt;

    auto distance = first.center.GetDistance(second.center);
    auto area = ComputeTriangleArea(first.radius, second.radius, distance);
    auto height = 2.0 * area / distance; // distance * height / 2 = area

    auto circle_dir = Vector(first.center, second.center);
    circle_dir.Normalize();
    if (IsObliqueAngle(first.radius, distance, second.radius))
    {
        circle_dir.Inverse();
    }

    auto circle_radius = height;
    auto circle_distance = std::sqrt(first.radius * first.radius - circle_radius * circle_radius);
    auto circle_center = first.center;
    circle_center.x += circle_dir.x * circle_distance;
    circle_center.y += circle_dir.y * circle_distance;
    circle_center.z += circle_dir.z * circle_distance;
    return SphereIntersectionResult{ circle_center, circle_dir, circle_radius };
}

math::Point ComputeLineIntersection(const math::Point& target_point, const math::Sphere& sphere, bool nearest)
{
    auto radius_dir = Vector(sphere.center, target_point);
    radius_dir.Normalize();
    if (!nearest)
    {
        radius_dir.Inverse();
    }
    return {
        sphere.center.x + radius_dir.x * sphere.radius,
        sphere.center.y + radius_dir.y * sphere.radius,
        sphere.center.z + radius_dir.z * sphere.radius
    };
}

double ComputeTriangleArea(double a, double b, double c)
{
    double p = 0.5 * (a + b + c);
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

bool IsObliqueAngle(double a, double b, double c)
{
    // c^2 = a^2 + b^2 - 2 * a * b * cos(alpha)
    // cos(alpha) = (a^2 + b^2 - c^2) / (2 * a * b)
    double cos_alpha = (a * a + b * b - c * c) / (2.0 * a * b);
    return cos_alpha < 0;
}

} // namespace copter::math
