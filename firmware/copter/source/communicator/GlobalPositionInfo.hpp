#ifndef GLOBAL_POSITION_INFO_HPP
#define GLOBAL_POSITION_INFO_HPP

#include <cstdint>
#include <iosfwd>

struct __mavlink_global_position_int_t;

namespace copter::communicator
{

struct GlobalPositionInfo
{
    std::uint32_t time_ms = {};
    float latitude_deg = {};
    float longitude_deg = {};
    float altitude_m = {};
    float relative_altitude_m = {};
    float speed_x_ms = {};
    float speed_y_ms = {};
    float speed_z_ms = {};
    float yaw_deg = {};

    GlobalPositionInfo(const __mavlink_global_position_int_t& global_position);
};

} // namespace copter::communicator

#endif
