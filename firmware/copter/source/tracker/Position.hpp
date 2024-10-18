#ifndef POSITION_HPP
#define POSITION_HPP

namespace copter::tracker
{

struct Position
{
    float latitude_deg = {};
    float longitude_deg = {};
    float altitude_m = {};
};

} // namespace copter::tracker

#endif