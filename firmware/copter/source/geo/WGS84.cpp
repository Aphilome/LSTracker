#include "WGS84.hpp"

#include <GeographicLib/Geocentric.hpp>

namespace
{

GeographicLib::Geocentric s_geocentric;

} // namespace

namespace copter::geo
{

math::Point ConvertToCartesian(const Position& position)
{
    math::Point point = {};
    s_geocentric.Forward(position.latitude_deg, position.longitude_deg, position.altitude_m, point.x, point.y, point.z);
    return point;
}

Position ConvertToGeoPosition(const math::Point& point)
{
    Position position = {};
    s_geocentric.Reverse(point.x, point.y, point.z, position.latitude_deg, position.longitude_deg, position.altitude_m);
    return position;
}

} // namespace copter::geo
