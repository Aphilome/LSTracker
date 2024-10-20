#ifndef GEOMETRIC_TRIANGULATION_HPP
#define GEOMETRIC_TRIANGULATION_HPP

#include "ITriangulationAlgorithm.hpp"

namespace copter::math
{

struct SphereIntersectionResult;

} // namespace copter::math

namespace copter::tracker
{

class GeometricTriangulation final
    : public ITriangulationAlgorithm
{
public:
    Result Execute(const std::vector<math::Sphere>& spheres) override;

private:
    Result FindCirclesIntersection(const math::SphereIntersectionResult& first, const math::SphereIntersectionResult& second);
};

} // namespace copter::tracker

#endif