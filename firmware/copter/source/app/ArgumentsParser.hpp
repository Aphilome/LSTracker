#ifndef ARGUMENTS_PARSER_HPP
#define ARGUMENTS_PARSER_HPP

#include <IChannel.hpp>

#include <argparse/argparse.hpp>

namespace copter::app
{

struct Arguments
{
    channel::Protocol protocol = channel::Protocol::Unknown;
    std::string address;
};

class ArgumentsParser
{
public:
    ArgumentsParser();

    std::string GetHelp() const;
    Arguments Parse(int argc, char** argv);

private:
    channel::Protocol ParseProtocol(const std::string& connection);
    std::string ParseAddress(const std::string& connection);

private:
    argparse::ArgumentParser m_parser;
};

} // namespace copter::app

#endif