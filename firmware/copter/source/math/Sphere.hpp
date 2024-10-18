#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point.hpp"

namespace copter::math
{

struct Sphere
{
    Point center = {};
    float radius = {};

    bool IsIntersected(const Sphere& first, const Sphere& second) const;
};

} // namespace copter::math

#endif