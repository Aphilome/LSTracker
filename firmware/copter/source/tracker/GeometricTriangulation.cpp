#include "GeometricTriangulation.hpp"

#include "math/Utility.hpp"

namespace copter::tracker
{

std::optional<math::Point> GeometricTriangulation::Execute(const std::vector<math::Sphere>& spheres)
{
    if (spheres.size() < 3)
        return std::nullopt;

    const auto& first = spheres[0];
    const auto& second = spheres[1];
    const auto& third = spheres[2];

    auto circle = ComputeSpheresIntersection(first, second);
    if (!circle)
    {
        // The spheres don't intersect due to the measurement error of the radiuses.
        auto first_sphere_point = ComputeLineIntersection(second.center, first, !first.IsInside(second));
        auto second_sphere_point = ComputeLineIntersection(first.center, second, !second.IsInside(first));
        auto middle_point = first_sphere_point.GetMiddle(second_sphere_point);
        auto third_sphere_point = ComputeLineIntersection(middle_point, third);
        return middle_point.GetMiddle(third_sphere_point);
    }

    return std::nullopt;
}

} // namespace copter::tracker
