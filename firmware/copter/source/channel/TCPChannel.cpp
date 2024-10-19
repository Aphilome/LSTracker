#include "TCPChannel.hpp"

namespace copter::channel
{
    
TCPChannel::TCPChannel(std::uint16_t port)
    : m_acceptor(port)
{
    m_socket = m_acceptor.accept();
}

Protocol TCPChannel::GetProtocol() const
{
    return Protocol::TCP;
}

std::size_t TCPChannel::Read(void* data, std::size_t length)
{
    return m_socket.read(data, length);
}

std::size_t TCPChannel::Write(const void* data, std::size_t length)
{
    return m_socket.write(data, length);
}

} // namespace copter::channel
