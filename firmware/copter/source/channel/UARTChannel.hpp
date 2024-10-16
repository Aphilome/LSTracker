#ifndef UART_CHANNEL_HPP
#define UART_CHANNEL_HPP

#include "IChannel.hpp"

namespace copter::channel
{

class UARTChannel final
    : public IChannel
{
public:
    bool Read(void* data, std::size_t length) override;
    bool Write(const void* data, std::size_t length) override;
};

} // namespace copter::channel

#endif
