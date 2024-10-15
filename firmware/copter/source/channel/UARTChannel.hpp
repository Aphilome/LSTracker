#ifndef UART_CHANNEL_HPP
#define UART_CHANNEL_HPP

#include "IChannel.hpp"

namespace copter::channel
{

class UARTChannel
    : public IChannel
{
public:
    bool Read(std::uint8_t& data, std::size_t length) override;
    bool Write(const std::uint8_t& data, std::size_t length) override;
};

} // namespace copter::channel

#endif
