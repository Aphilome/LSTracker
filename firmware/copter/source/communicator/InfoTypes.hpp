#ifndef INFO_TYPES_HPP
#define INFO_TYPES_HPP

namespace copter::communicator
{

struct GlobalPositionInfo
{
    float time_ms = {};
    float latitude = {};
    float longitude = {};
    float altitude = {};
    float speed_x = {};
    float speed_y = {};
    float speed_z = {};
    float yaw_deg = {};
};

} // namespace copter::communicator

#endif
