
#include "GPSRawInfo.hpp"

#include <common/mavlink.h>

namespace copter::communicator
{

GPSRawInfo::GPSRawInfo(const mavlink_gps_raw_int_t& gps_raw)
    : time_us(gps_raw.time_usec)
    , latitude_deg(gps_raw.lat / 10'000'000.0)
    , longitude_deg(gps_raw.lon / 10'000'000.0)
    , altitude_m(gps_raw.alt / 1000.0)
{
}

} // namespace copter::communicator
