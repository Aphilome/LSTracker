#ifndef GEOMETRIC_TRIANGULATION_HPP
#define GEOMETRIC_TRIANGULATION_HPP

#include "ITriangulationAlgorithm.hpp"

namespace copter::tracker
{

class GeometricTriangulation final
    : public ITriangulationAlgorithm
{
public:
    std::optional<math::Point> Execute(const std::vector<math::Sphere>& spheres) override;
};

} // namespace copter::tracker

#endif