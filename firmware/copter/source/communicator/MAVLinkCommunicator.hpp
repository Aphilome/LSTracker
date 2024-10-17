#ifndef MAV_LINK_COMMUNICATOR_HPP
#define MAV_LINK_COMMUNICATOR_HPP

#include "InfoTypes.hpp"

#include <atomic>
#include <vector>
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

class MAVLinkCommunicator
{
public:
    MAVLinkCommunicator(channel::IChannel& channel);
    ~MAVLinkCommunicator();

    void AddGlobalPositionCallback(GlobalPositionInfoCallback callback);

private:
    void ReadThread();
    bool ReadMessage(__mavlink_message& message);
    void ProcessMessage(const __mavlink_message& message);

private:
    channel::IChannel& m_channel;

    std::vector<uint8_t> m_buffer;
    std::size_t m_data_size = 0;
    std::size_t m_data_index = 0;

    std::thread m_read_thread;
    std::atomic_bool m_is_working = true;
};

} // namespace copter::communicator

#endif
