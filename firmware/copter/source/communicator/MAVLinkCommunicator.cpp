#include "MAVLinkCommunicator.hpp"

#include "channel/IChannel.hpp"

#include <common/mavlink.h>

#include <chrono>
#include <thread>

namespace
{


std::size_t DetermineStreamBufferSize(copter::channel::IChannel& channel)
{
    using copter::channel::Protocol;

    constexpr std::size_t max_socket_package_size = 1500;

    switch (channel.GetProtocol())
    {
        case Protocol::TCP:  return max_socket_package_size;
        case Protocol::UDP:  return max_socket_package_size;
        case Protocol::UART: return 0;
        default:             return 0;
    }
}

} // namespace

namespace copter::communicator
{

MAVLinkCommunicator::MAVLinkCommunicator(channel::IChannel& channel)
    : m_byte_stream(channel, DetermineStreamBufferSize(channel))
{
}

MAVLinkCommunicator::~MAVLinkCommunicator()
{
    Stop();
}

void MAVLinkCommunicator::SetGlobalPositionCallback(GlobalPositionInfoCallback callback)
{
    m_global_position_callback = std::move(callback);
}

void MAVLinkCommunicator::SetGPSRawCallback(GPSRawInfoCallback callback)
{
    m_gps_raw_callback = std::move(callback);
}

void MAVLinkCommunicator::Stop()
{
    m_is_working = false;
}

void MAVLinkCommunicator::ReadMessagesLoop(std::uint32_t sleep_us)
{
    using namespace std::chrono_literals;

    m_is_working = true;

    mavlink_message_t message = {};

    while (m_is_working)
    {
        bool is_success = ReadMessage(message);
        if (is_success)
        {
            ProcessMessage(message);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_us));
        }
    }
}

bool MAVLinkCommunicator::ReadMessage(mavlink_message_t& message)
{
    std::uint8_t byte = {};
    mavlink_status_t status = {};

    while (m_byte_stream.ReadNext(byte))
    {
        if (mavlink_parse_char(MAVLINK_COMM_1, byte, &message, &status))
        {
            return true;
        }
    }

    return false;
}

void MAVLinkCommunicator::ProcessMessage(const mavlink_message_t& message)
{
    switch (message.msgid)
    {
        case MAVLINK_MSG_ID_GPS_RAW_INT:
        {
            ProcessGPSRawMessage(message);
            break;
        }

        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
        {
            ProcessGlobalPositionMessage(message);
            break;
        }

        default:
            break;
    }
}

void MAVLinkCommunicator::ProcessGlobalPositionMessage(const mavlink_message_t& message)
{
    if (!m_global_position_callback)
        return;

    mavlink_global_position_int_t global_position;
    mavlink_msg_global_position_int_decode(&message, &global_position);
    m_global_position_callback(GlobalPositionInfo(global_position));
}

void MAVLinkCommunicator::ProcessGPSRawMessage(const mavlink_message_t& message)
{
    if (!m_gps_raw_callback)
        return;

    mavlink_gps_raw_int_t gps_raw;
    mavlink_msg_gps_raw_int_decode(&message, &gps_raw);
    m_gps_raw_callback(GPSRawInfo(gps_raw));
}

} // namespace copter::communicator
