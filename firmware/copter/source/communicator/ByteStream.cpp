#include "ByteStream.hpp"

#include "channel/IChannel.hpp"

namespace copter::communicator
{

ByteStream::ByteStream(channel::IChannel& channel, std::size_t buffer_size)
    : m_channel(channel)
    , m_buffer(buffer_size)
{
}

bool ByteStream::ReadNext(std::uint8_t& byte)
{
    if (m_buffer.empty())
    {
        auto bytes_read = m_channel.Read(&byte, 1);
        return bytes_read != -1;
    }

    if (m_data_index >= m_data_size)
    {
        auto read_bytes = m_channel.Read(m_buffer.data(), m_buffer.size());
        if (read_bytes <= 0)
            return false;

        m_data_size = static_cast<std::size_t>(read_bytes);
        m_data_index = 0;
    }

    byte = m_buffer[m_data_index];
    ++m_data_index;
    return true;
}

} // namespace copter::communicator
