#ifndef ICHANNEL_HPP
#define ICHANNEL_HPP

#include <memory>
#include <string>
#include <cstddef>
#include <cstdint>

namespace copter::channel
{

class IChannel
{
public:
    virtual ~IChannel() = default;
    virtual bool Read(std::uint8_t& data, std::size_t length) = 0;
    virtual bool Write(const std::uint8_t& data, std::size_t length) = 0;
};

enum class Protocol
{
    TCP,
    UART,
};

std::unique_ptr<IChannel> Open(Protocol protocol, const std::string& address);

} // namespace copter::channel

#endif