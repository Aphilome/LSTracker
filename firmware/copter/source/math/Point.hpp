#ifndef POINT_HPP
#define POINT_HPP

namespace copter::math
{

struct Point
{
    double x = {};
    double y = {};
    double z = {};

    double GetDistance(const Point& other) const;
    Point GetMiddle(const Point& other) const;
};


} // namespace copter::math

#endif