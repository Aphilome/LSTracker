#ifndef UDP_CHANNEL_HPP
#define UDP_CHANNEL_HPP

#include "IChannel.hpp"

#include <sockpp/udp_socket.h>

#include <string>
#include <cstdint>

namespace copter::channel
{

class UDPChannel final
    : public IChannel
{
public:
    UDPChannel(const std::string& host, std::uint16_t port);

    std::size_t Read(void* data, std::size_t length) override;
    std::size_t Write(const void* data, std::size_t length) override;

private:
    sockpp::udp_socket m_socket;
};

} // namespace copter::channel

#endif
