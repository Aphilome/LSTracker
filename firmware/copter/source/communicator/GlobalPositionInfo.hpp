#ifndef GLOBAL_POSITION_INFO_HPP
#define GLOBAL_POSITION_INFO_HPP

#include <cstdint>

struct __mavlink_global_position_int_t;

namespace copter::communicator
{

struct GlobalPositionInfo
{
    std::uint32_t time_boot_ms = {};
    double latitude_deg = {};
    double longitude_deg = {};
    double altitude_m = {};
    double relative_altitude_m = {};
    double speed_x_ms = {};
    double speed_y_ms = {};
    double speed_z_ms = {};
    double yaw_deg = {};

    GlobalPositionInfo(const __mavlink_global_position_int_t& global_position);
};

} // namespace copter::communicator

#endif
