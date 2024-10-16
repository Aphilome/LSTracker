#include "IChannel.hpp"

#include "TCPChannel.hpp"
#include "UDPChannel.hpp"
#include "UARTChannel.hpp"

#include <mutex>
#include <cstdint>
#include <utility>

namespace
{

std::once_flag s_init_flag;

void InitSockets()
{
    std::call_once(s_init_flag, sockpp::initialize);
}

std::pair<std::string, std::uint64_t> SplitAddress(const std::string& address)
{
    auto comma_pos = address.find(':');
    if (comma_pos == std::string::npos)
        return {};

    auto name = address.substr(0, comma_pos);
    auto value = std::stoull(address.substr(comma_pos + 1));
    return {std::move(name), value};
}

} // namespace


namespace copter::channel
{

std::unique_ptr<IChannel> Open(Protocol protocol, const std::string& address)
{
    if (protocol == Protocol::TCP || protocol == Protocol::UDP)
    {
        InitSockets();
    }

    switch (protocol)
    {
    case Protocol::TCP:
    {
        auto port = std::stoul(address);
        return std::make_unique<TCPChannel>(static_cast<std::uint16_t>(port));
    }

     case Protocol::UDP:
     {
        auto [host, port] = SplitAddress(address);
        return std::make_unique<UDPChannel>(host, static_cast<std::uint16_t>(port));
     }

    case Protocol::UART:
    {
        auto [device, baudrate] = SplitAddress(address);
        return std::make_unique<UARTChannel>(device, baudrate);
    }

    default:
        return nullptr;
    }
}


} // namespace copter::channel
