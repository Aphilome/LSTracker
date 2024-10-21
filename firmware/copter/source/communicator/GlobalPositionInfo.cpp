#include "GlobalPositionInfo.hpp"

#include <common/mavlink.h>

namespace copter::communicator
{

GlobalPositionInfo::GlobalPositionInfo(const mavlink_global_position_int_t& global_position)
    : time_boot_ms(global_position.time_boot_ms)
    , latitude_deg(global_position.lat / 10'000'000.0)
    , longitude_deg(global_position.lon / 10'000'000.0)
    , altitude_m(global_position.alt / 1000.0)
    , relative_altitude_m(global_position.relative_alt / 1000.0)
    , speed_x_ms(global_position.vx / 100.0)
    , speed_y_ms(global_position.vy / 100.0)
    , speed_z_ms(global_position.vz / 100.0)
    , yaw_deg(global_position.hdg / 100.0)
{
}

} // namespace copter::communicator
