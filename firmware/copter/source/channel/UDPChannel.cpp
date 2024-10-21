#include "UDPChannel.hpp"

namespace copter::channel
{
    
UDPChannel::UDPChannel(const std::string& host, std::uint16_t port)
    : m_socket(sockpp::inet_address(host, port))
{
}

Protocol UDPChannel::GetProtocol() const
{
    return Protocol::UDP;
}

std::size_t UDPChannel::Read(void* data, std::size_t length)
{
    return m_socket.recv(data, length);
}

std::size_t UDPChannel::Write(const void* data, std::size_t length)
{
    return m_socket.send(data, length);
}

} // namespace copter::channel
