#include "IChannel.hpp"

#include "TCPChannel.hpp"
#include "UARTChannel.hpp"

namespace copter::channel
{

std::unique_ptr<IChannel> Open(Protocol protocol, const std::string& address)
{
    IChannel* channel = nullptr;

    switch (protocol)
    {
    case Protocol::TCP:
        channel = new TCPChannel();
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
