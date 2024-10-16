#include <IChannel.hpp>

#include <argparse/argparse.hpp>

#include <memory>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iostream>

namespace copter::app
{

struct Arguments
{
    copter::channel::Protocol protocol = copter::channel::Protocol::Unknown;
    std::string address;
};

copter::channel::Protocol ParseProtocol(const std::string& connection)
{
    using namespace copter::channel;

    auto comma_pos = connection.find(':');
    if (comma_pos == std::string::npos)
        return Protocol::Unknown;

    auto protocol = connection.substr(0, comma_pos);
    std::transform(protocol.begin(), protocol.end(), protocol.begin(), [](unsigned char c)
    {
        return std::tolower(c);
    });

    if (protocol == "tcp")
        return Protocol::TCP;
    if (protocol == "udp")
        return Protocol::UDP;
    if (protocol == "uart")
        return Protocol::UART;

    return Protocol::Unknown;;
}

std::string ParseAddress(const std::string& connection)
{
    auto comma_pos = connection.find(':');
    if (comma_pos == std::string::npos)
        return {};

    return connection.substr(comma_pos + 1);
}

Arguments ParseArguments(argparse::ArgumentParser& program, int argc, char* argv[])
{
    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    auto connection = program.get("-c");;

    Arguments arguments = {};
    arguments.protocol = ParseProtocol(connection);
    arguments.address = ParseAddress(connection);
    return arguments;
}

std::unique_ptr<argparse::ArgumentParser> CreateArgumentsParser(const std::string& program_name)
{
    auto parser = std::make_unique<argparse::ArgumentParser>(program_name);
    parser->add_description("Local position system for Ardupilot based copters");

    parser->add_argument("-c", "--connection")
        .required()
        .help("address for connecting to the copter: tcp:<port> or udp:<host>:<port> or uart:<device>:<baudrate>");

    return parser;
}

} // namespace copter::app


int main(int argc, char* argv[])
{
    using namespace copter::app;

    auto parser = CreateArgumentsParser("copter-app");
    auto arguments = ParseArguments(*parser, argc, argv);

    std::cerr << "Connecting to " << arguments.address << std::endl;

    auto channel = copter::channel::Open(arguments.protocol, arguments.address);
    if (!channel)
    {
        std::cerr << "Failed to open channel" << std::endl;
        return EXIT_FAILURE;
    }

    int data = 0;
    auto is_success = channel->Read(&data, sizeof(data));
    if (!is_success)
    {
        std::cerr << "Failed to read data from channel" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Data: " << data << std::endl;

    return EXIT_SUCCESS;
}
