#include "UDPChannel.hpp"

namespace copter::channel
{
    
UDPChannel::UDPChannel(const std::string& host, std::uint16_t port)
    : m_socket(sockpp::inet_address(host, port))
{
}

bool UDPChannel::Read(void* data, std::size_t length)
{
    auto read_bytes = m_socket.recv(data, length);
    return read_bytes != -1;
}

bool UDPChannel::Write(const void* data, std::size_t length)
{
    auto sent_bytes = m_socket.send(data, length);
    return sent_bytes != -1;
}

} // namespace copter::channel
