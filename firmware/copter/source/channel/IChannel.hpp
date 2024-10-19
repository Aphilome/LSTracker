#ifndef ICHANNEL_HPP
#define ICHANNEL_HPP

#include <memory>
#include <string>
#include <iterator>

namespace copter::channel
{

enum class Protocol
{
    TCP,
    UDP,
    UART,
    Unknown
};

class IChannel
{
public:
    virtual ~IChannel() = default;
    
    virtual Protocol GetProtocol() const = 0;
    virtual std::size_t Read(void* data, std::size_t length) = 0;
    virtual std::size_t Write(const void* data, std::size_t length) = 0;
};

std::unique_ptr<IChannel> Open(Protocol protocol, const std::string& address);

} // namespace copter::channel

#endif