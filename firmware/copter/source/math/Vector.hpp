#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"

namespace copter::math
{

struct Vector
{
    float x = {};
    float y = {};
    float z = {};

    Vector() = default;

    Vector(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {}

    Vector(const Point& begin, const Point& end)
        : x(end.x - begin.x)
        , y(end.y - begin.y)
        , z(end.z - begin.z)
    {}

    float GetLength() const;
    void Normalize();
};

} // namespace copter::math

#endif