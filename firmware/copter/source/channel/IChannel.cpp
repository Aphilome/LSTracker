#include "IChannel.hpp"

#include "TCPChannel.hpp"
#include "UDPChannel.hpp"
#include "UARTChannel.hpp"

#include <mutex>

namespace
{

std::once_flag s_init_flag;

void InitSockets()
{
    std::call_once(s_init_flag, sockpp::initialize);
}

} // namespace


namespace copter::channel
{

std::unique_ptr<IChannel> Open(Protocol protocol, const std::string& address)
{
    IChannel* channel = nullptr;

    switch (protocol)
    {
    case Protocol::TCP:
        InitSockets();
        channel = new TCPChannel("127.0.0.1", 50000);
        break;

     case Protocol::UDP:
        InitSockets();
        channel = new UDPChannel("127.0.0.1", 50001);
        break;

    case Protocol::UART:
        channel = new UARTChannel();
        break;

    default:
        break;
    }

    return std::unique_ptr<IChannel>(channel);
}


} // namespace copter::channel
