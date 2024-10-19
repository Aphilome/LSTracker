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

    auto circle = ComputeIntersection(first, second);
    if (!circle)
    {
        // The spheres don't intersect due to the measurement error of the radiuses.
        auto first_nearest_point = ComputeNearestPoint(second.center, first);
        auto second_nearest_point = ComputeNearestPoint(first.center, second);
        auto middle_point = first_nearest_point.GetMiddle(second_nearest_point);
        auto third_nearest_point = ComputeNearestPoint(middle_point, third);
        return middle_point.GetMiddle(third_nearest_point);
    }

    return std::nullopt;
}

} // namespace copter::tracker
