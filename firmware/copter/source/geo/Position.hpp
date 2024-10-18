#ifndef POSITION_HPP
#define POSITION_HPP

namespace copter::geo
{

struct Position
{
    float latitude_deg = {};
    float longitude_deg = {};
    float altitude_m = {};
};

} // namespace copter::geo

#endif