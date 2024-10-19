#ifndef POSITION_HPP
#define POSITION_HPP

namespace copter::geo
{

struct Position
{
    double latitude_deg = {};
    double longitude_deg = {};
    double altitude_m = {};
};

} // namespace copter::geo

#endif