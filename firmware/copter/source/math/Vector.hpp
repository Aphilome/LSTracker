#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"

namespace copter::math
{

struct Vector
{
    double x = {};
    double y = {};
    double z = {};

    Vector() = default;

    Vector(double x, double y, double z)
        : x(x)
        , y(y)
        , z(z)
    {}

    Vector(const Point& begin, const Point& end)
        : x(end.x - begin.x)
        , y(end.y - begin.y)
        , z(end.z - begin.z)
    {}

    double GetLength() const;
    void Normalize();
    void Inverse();
};

} // namespace copter::math

#endif