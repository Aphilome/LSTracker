#ifndef ITRIANGULATION_ALGORITHM_HPP
#define ITRIANGULATION_ALGORITHM_HPP

#include "math/Sphere.hpp"

#include <vector>
#include <optional>

namespace copter::tracker
{

class ITriangulationAlgorithm
{
public:
    virtual ~ITriangulationAlgorithm() = default;

    virtual std::optional<math::Point> Execute(const std::vector<math::Sphere>& spheres) = 0;
};

} // namespace copter::tracker

#endif