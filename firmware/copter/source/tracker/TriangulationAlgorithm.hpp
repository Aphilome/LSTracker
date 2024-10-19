#ifndef TRIANGULATION_ALGORITHM_HPP
#define TRIANGULATION_ALGORITHM_HPP

#include "math/Sphere.hpp"

#include <vector>
#include <optional>

namespace copter::tracker
{

class TriangulationAlgorithm
{
public:
    std::optional<math::Point> Execute(const std::vector<math::Sphere>& spheres);
};

} // namespace copter::tracker

#endif