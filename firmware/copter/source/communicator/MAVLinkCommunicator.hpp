#ifndef MAV_LINK_COMMUNICATOR_HPP
#define MAV_LINK_COMMUNICATOR_HPP

#include "ByteStream.hpp"
#include "GlobalPositionInfo.hpp"
#include "GPSRawInfo.hpp"

#include <atomic>
#include <thread>
#include <cstdint>
#include <functional>

struct __mavlink_message;

namespace copter::channel
{

class IChannel;

} // namespace copter::channel

namespace copter::communicator
{

using GlobalPositionInfoCallback = std::function<void(const GlobalPositionInfo&)>;
using GPSRawInfoCallback = std::function<void(const GPSRawInfo&)>;

class MAVLinkCommunicator
{
public:
    MAVLinkCommunicator(channel::IChannel& channel);
    ~MAVLinkCommunicator();

    void SetGlobalPositionCallback(GlobalPositionInfoCallback callback);
    void SetGPSRawCallback(GPSRawInfoCallback callback);

private:
    using mavlink_message_t = __mavlink_message;

    void ReadThread();
    bool ReadMessage(mavlink_message_t& message);
    void ProcessMessage(const mavlink_message_t& message);
    void ProcessGlobalPositionMessage(const mavlink_message_t& message);
    void ProcessGPSRawMessage(const mavlink_message_t& message);

private:
    ByteStream m_byte_stream;
    std::thread m_read_thread;
    std::atomic_bool m_is_working = true;

    GlobalPositionInfoCallback m_global_position_callback = {};
    GPSRawInfoCallback m_gps_raw_callback = {};
};

} // namespace copter::communicator

#endif
