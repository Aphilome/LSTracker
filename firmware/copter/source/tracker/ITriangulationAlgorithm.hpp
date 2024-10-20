#ifndef ITRIANGULATION_ALGORITHM_HPP
#define ITRIANGULATION_ALGORITHM_HPP

#include "math/Sphere.hpp"

#include <vector>
#include <utility>
#include <optional>

namespace copter::tracker
{

class ITriangulationAlgorithm
{
public:
    using NullablePoint = std::optional<math::Point>;
    using Result = std::pair<NullablePoint, NullablePoint>;

    virtual ~ITriangulationAlgorithm() = default;

    virtual Result Execute(const std::vector<math::Sphere>& spheres) = 0;
};

} // namespace copter::tracker

#endif