#ifndef TCP_CHANNEL_HPP
#define TCP_CHANNEL_HPP

#include "IChannel.hpp"

#include <sockpp/tcp_acceptor.h>

#include <string>
#include <cstdint>

namespace copter::channel
{

class TCPChannel final
    : public IChannel
{
public:
    TCPChannel(std::uint16_t port);

    bool Read(void* data, std::size_t length) override;
    bool Write(const void* data, std::size_t length) override;

private:
    sockpp::tcp_acceptor m_acceptor;
    sockpp::tcp_socket m_socket;
};

} // namespace copter::channel

#endif
