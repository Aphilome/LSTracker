#include "MAVLinkCommunicator.hpp"

#include "channel/IChannel.hpp"

#include <common/mavlink.h>

#include <chrono>
#include <iostream>
#include <algorithm>

namespace
{

constexpr std::size_t max_package_size = 1500;

} // namespace

namespace copter::communicator
{

MAVLinkCommunicator::MAVLinkCommunicator(channel::IChannel& channel)
    : m_byte_stream(channel, max_package_size)
    , m_read_thread([this] { ReadThread(); })
{
}

MAVLinkCommunicator::~MAVLinkCommunicator()
{
    m_is_working = false;
}

void MAVLinkCommunicator::SetGlobalPositionCallback(GlobalPositionInfoCallback callback)
{
    m_global_position_callback = std::move(callback);
}

void MAVLinkCommunicator::ReadThread()
{
    using namespace std::chrono_literals;

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
            std::this_thread::sleep_for(100us);
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
        case MAVLINK_MSG_ID_HEARTBEAT:
        {
            //std::cout << "MAVLINK_MSG_ID_HEARTBEAT" << std::endl;
            break;
        }

        case MAVLINK_MSG_ID_GPS_RAW_INT:
        {
            //std::cout << "MAVLINK_MSG_ID_GPS_RAW_INT" << std::endl;
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

} // namespace copter::communicator
