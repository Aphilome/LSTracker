#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point.hpp"

namespace copter::math
{

struct Sphere
{
    Point center = {};
    double radius = {};

    bool IsIntersected(const Sphere& other) const;
};

} // namespace copter::math

#endif