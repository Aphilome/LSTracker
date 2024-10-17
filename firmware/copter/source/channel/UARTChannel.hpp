#ifndef UART_CHANNEL_HPP
#define UART_CHANNEL_HPP

#include "IChannel.hpp"

#include <string>
#include <cstdint>

namespace copter::channel
{

class UARTChannel final
    : public IChannel
{
public:
    UARTChannel(const std::string& device, std::uint64_t baudrate) {}

    std::size_t Read(void* data, std::size_t length) override;
    std::size_t Write(const void* data, std::size_t length) override;
};

} // namespace copter::channel

#endif
