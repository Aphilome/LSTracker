#include "Intersection.hpp"
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
    circle_center.Move(circle_dir, circle_distance);

    return SphereIntersectionResult{ circle_center, circle_dir, circle_radius };
}

std::optional<SphereIntersectionResult> ComputeSphereAndPlaneIntersection(const Sphere& sphere, const Point& plane_point, const Vector& plane_normal)
{
    // Plane:
    // nx * (x - x0) + ny * (y - y0)  + nz * (z - xz)  = 0 
    // A * x + B * y + C * z + D = 0
    // A = nx; B = ny; C = nz; D = -nx * x0 - ny * y0 - nz * z0
    auto d = -plane_normal.x * plane_point.x - plane_normal.y * plane_point.y - plane_normal.z * plane_point.z;
    auto circle_distance = plane_normal.x * sphere.center.x + plane_normal.y * sphere.center.y + plane_normal.z * sphere.center.z;
    if (circle_distance > sphere.radius)
        return std::nullopt;

    auto circle_center = sphere.center;
    circle_center.Move(plane_normal, circle_distance);

    auto circle_radius = std::sqrt(sphere.radius * sphere.radius - circle_distance * circle_distance);
    return SphereIntersectionResult{ circle_center, plane_normal, circle_radius };
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

} // namespace copter::math
