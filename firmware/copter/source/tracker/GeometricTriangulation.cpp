#include "GeometricTriangulation.hpp"

#include "math/Triangle.hpp"
#include "math/Intersection.hpp"

#include <cmath>

namespace copter::tracker
{

ITriangulationAlgorithm::Result GeometricTriangulation::Execute(const std::vector<math::Sphere>& spheres)
{
    if (spheres.size() < 3)
        return {};

    const auto& first = spheres[0];
    const auto& second = spheres[1];
    const auto& third = spheres[2];

    auto first_intersection_result = ComputeSpheresIntersection(first, second);
    if (!first_intersection_result)
    {
        // The spheres don't intersect due to the measurement error of the radiuses.
        auto first_sphere_point = ComputeLineIntersection(second.center, first, !first.IsInside(second));
        auto second_sphere_point = ComputeLineIntersection(first.center, second, !second.IsInside(first));
        auto middle_point = first_sphere_point.GetMiddle(second_sphere_point);
        auto third_sphere_point = ComputeLineIntersection(middle_point, third);
        auto result_point = middle_point.GetMiddle(third_sphere_point);
        return { result_point, std::nullopt };
    }

    const auto& circle = first_intersection_result.value();
    auto second_intersection_result = ComputeSphereAndPlaneIntersection(third, circle.center, circle.normal);
    if (!second_intersection_result)
    {
        // There is no intersection between plane and sphere.
        // TODO: handle this case.
        return {};
    }

    return FindCirclesIntersection(first_intersection_result.value(), second_intersection_result.value());
}

ITriangulationAlgorithm::Result GeometricTriangulation::FindCirclesIntersection(const math::SphereIntersectionResult& first, const math::SphereIntersectionResult& second)
{
    using namespace math;

    auto dir = Vector(first.center, second.center);
    auto circles_distance = dir.GetLength();
    auto area = ComputeTriangleArea(first.radius, second.radius, circles_distance);
    auto height = 2.0 * area / circles_distance;

    auto left_dir = Vector(
        first.normal.y * dir.z - first.normal.z * dir.y,
        first.normal.z * dir.x - first.normal.x * dir.z,
        first.normal.x * dir.y - first.normal.y * dir.x
    );
    left_dir.Normalize();
    dir.Normalize();

    auto point_offset = std::sqrt(first.radius * first.radius - height * height);
    auto point = first.center;
    point.Move(dir, point_offset);

    auto first_result = point;
    first_result.Move(left_dir, height);

    auto second_result = point;
    second_result.Move(left_dir, -height);

    return { first_result, second_result };
}

} // namespace copter::tracker
