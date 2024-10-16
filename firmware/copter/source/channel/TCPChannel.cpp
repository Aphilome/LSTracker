#include "TCPChannel.hpp"

namespace copter::channel
{
    
TCPChannel::TCPChannel(std::uint16_t port)
    : m_acceptor(port)
{
    m_socket= m_acceptor.accept();
}

bool TCPChannel::Read(void* data, std::size_t length)
{
    auto read_bytes = m_socket.read(data, length);
    return read_bytes != -1;
}

bool TCPChannel::Write(const void* data, std::size_t length)
{
    auto written_bytes = m_socket.write(data, length);
    return written_bytes != -1;
}

} // namespace copter::channel
