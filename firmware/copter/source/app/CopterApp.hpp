#ifndef COPTER_APP_HPP
#define COPTER_APP_HPP

#include "ArgumentsParser.hpp"

#include "channel/IChannel.hpp"

#include <optional>

namespace copter::app
{

class CopterApp
{
public:
    int Run(int argc, char** argv);

private:
    std::optional<Arguments> ParseArguments(int argc, char** argv) const;
    std::unique_ptr<channel::IChannel> OpenChannel(const Arguments& arguments);
};

} // namespace copter::app

#endif