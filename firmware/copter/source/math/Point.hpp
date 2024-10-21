#ifndef POINT_HPP
#define POINT_HPP

namespace copter::math
{

struct Vector;

struct Point
{
    double x = {};
    double y = {};
    double z = {};

    double GetDistance(const Point& other) const;
    Point GetMiddle(const Point& other) const;
    void Move(const Vector& normal, double distance);
};


} // namespace copter::math

#endif