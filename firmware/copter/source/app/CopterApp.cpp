#include "CopterApp.hpp"

#include "ArgumentsParser.hpp"

#include "communicator/MAVLinkCommunicator.hpp"

namespace copter::app
{

int CopterApp::Run(int argc, char** argv)
{
    auto arguments = ParseArguments(argc, argv);
    if (!arguments)
        return EXIT_FAILURE;

    auto channel = OpenChannel(arguments.value());
    if (!channel)
        return EXIT_FAILURE;

    auto communicator = communicator::MAVLinkCommunicator(*channel);
    while (true) {}
    return EXIT_SUCCESS;
}

std::optional<Arguments> CopterApp::ParseArguments(int argc, char** argv) const
{
    Arguments arguments = {};
    arguments.protocol = channel::Protocol::UDP;
    arguments.address = "127.0.0.1:50000";
    return arguments;

    /*ArgumentsParser parser;

    try
    {
        return parser.Parse(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl << std::endl;
        std::cerr << parser.GetHelp() << std::endl;
        return std::nullopt;
    }*/
}

std::unique_ptr<channel::IChannel> CopterApp::OpenChannel(const Arguments& arguments)
{
    try
    {
        return channel::Open(arguments.protocol, arguments.address);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl << std::endl;
        return nullptr;
    }
}

} // namespace copter::app
