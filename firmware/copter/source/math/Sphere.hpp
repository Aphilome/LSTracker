#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point.hpp"

namespace copter::math
{

struct Sphere
{
    Point center = {};
    float radius = {};
};

} // namespace copter::math

#endif