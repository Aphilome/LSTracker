#ifndef GPS_RAW_INFO_HPP
#define GPS_RAW_INFO_HPP

#include <cstdint>

struct __mavlink_gps_raw_int_t;

namespace copter::communicator
{

struct GPSRawInfo
{
    std::uint64_t time_us = {};
    float latitude_deg = {};
    float longitude_deg = {};
    float altitude_m = {};

    // If necessary, add other fields

    GPSRawInfo(const __mavlink_gps_raw_int_t& gps_raw);
};

} // namespace copter::communicator

#endif
