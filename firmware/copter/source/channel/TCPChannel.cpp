#include "TCPChannel.hpp"

namespace copter::channel
{
    
TCPChannel::TCPChannel(const std::string& host, std::uint16_t port)
    : m_connection(sockpp::inet_address(host, port))
{
}

bool TCPChannel::Read(void* data, std::size_t length)
{
    auto read_bytes = m_connection.read(data, length);
    return read_bytes != -1;
}

bool TCPChannel::Write(const void* data, std::size_t length)
{
    auto written_bytes = m_connection.write(data, length);
    return written_bytes != -1;
}

} // namespace copter::channel
