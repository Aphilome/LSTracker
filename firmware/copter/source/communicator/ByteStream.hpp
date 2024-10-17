#ifndef BYTE_STREAM_HPP
#define BYTE_STREAM_HPP

#include <vector>
#include <cstdint>

namespace copter::channel
{

class IChannel;

} // namespace copter::channel

namespace copter::communicator
{

class ByteStream
{
public:
    ByteStream(channel::IChannel& channel, std::size_t buffer_size);

    bool ReadNext(std::uint8_t& byte);

private:
    channel::IChannel& m_channel;
    std::vector<std::uint8_t> m_buffer;
    std::size_t m_data_size = 0;
    std::size_t m_data_index = 0;
};

} // namespace copter::communicator

#endif
