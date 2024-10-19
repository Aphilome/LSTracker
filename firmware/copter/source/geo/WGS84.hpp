#ifndef WGS84_HPP
#define WGS84_HPP

#include "Position.hpp"
#include "math/Point.hpp"

namespace copter::geo
{

math::Point ConvertToCartesian(const Position& position);

Position ConvertToGeoPosition(const math::Point& point);

} // namespace copter::geo

#endif