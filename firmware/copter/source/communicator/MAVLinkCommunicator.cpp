#include "MAVLinkCommunicator.hpp"

#include "channel/IChannel.hpp"

#include <common/mavlink.h>

#include <chrono>
#include <iostream>
#include <algorithm>

namespace copter::communicator
{

MAVLinkCommunicator::MAVLinkCommunicator(channel::IChannel& channel)
    : m_channel(channel)
    , m_read_thread([this] { ReadThread(); })
{
    constexpr std::size_t max_package_size = 1500;
    m_buffer.resize(max_package_size);
}

MAVLinkCommunicator::~MAVLinkCommunicator()
{
    m_is_working = false;
}

void MAVLinkCommunicator::AddGlobalPositionCallback(GlobalPositionInfoCallback callback)
{
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
    if (m_data_index >= m_data_size)
    {
        auto read_bytes = m_channel.Read(m_buffer.data(), m_buffer.size());
        m_data_index = 0;
        m_data_size = std::max<std::size_t>(0, read_bytes);
    }

    mavlink_status_t status = {};

    for ( ; m_data_index < m_data_size; ++m_data_index)
    {
        if (mavlink_parse_char(MAVLINK_COMM_1, m_buffer[m_data_index], &message, &status))
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
            std::cout << "MAVLINK_MSG_ID_HEARTBEAT" << std::endl;
            break;
        }

        case MAVLINK_MSG_ID_GPS_RAW_INT:
        {
            std::cout << "MAVLINK_MSG_ID_GPS_RAW_INT" << std::endl;
            break;
        }

        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
        {
            std::cout << "MAVLINK_MSG_ID_GLOBAL_POSITION_INT" << std::endl;
            break;
        }

        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV:
        {
            std::cout << "MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV" << std::endl;
            break;
        }

        case MAVLINK_MSG_ID_HIL_GPS:
        {
            std::cout << "MAVLINK_MSG_ID_HIL_GPS" << std::endl;
            break;
        }

        case MAVLINK_MSG_ID_GPS2_RAW:
        {
            std::cout << "MAVLINK_MSG_ID_GPS2_RAWS" << std::endl;
            break;
        }

        case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
        {
            std::cout << "MAVLINK_MSG_ID_LOCAL_POSITION_NED" << std::endl;
            break;
        }

        default:
            break;
    }
}

} // namespace copter::communicator
