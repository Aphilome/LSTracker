#include "ArgumentsParser.hpp"

namespace copter::app
{

ArgumentsParser::ArgumentsParser()
    : m_parser("copter-app")
{
    m_parser.add_description("Local position system for Ardupilot based copters");

    m_parser.add_argument("-c", "--connection")
        .required()
        .help("address for connecting to the copter: tcp:<port> or udp:<host>:<port> or uart:<device>:<baudrate>");    
}

std::string ArgumentsParser::GetHelp() const
{
    return m_parser.help().str();
}

Arguments ArgumentsParser::Parse(int argc, char** argv)
{
    m_parser.parse_args(argc, argv);

    auto connection = m_parser.get("-c");;

    Arguments arguments = {};
    arguments.protocol = ParseProtocol(connection);
    arguments.address = ParseAddress(connection);
    return arguments;
}

channel::Protocol ArgumentsParser::ParseProtocol(const std::string& connection)
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

std::string ArgumentsParser::ParseAddress(const std::string& connection)
{
    auto comma_pos = connection.find(':');
    if (comma_pos == std::string::npos)
        return {};

    return connection.substr(comma_pos + 1);
}

} // namespace copter::app