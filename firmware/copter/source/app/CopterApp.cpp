#include "CopterApp.hpp"

#include "ArgumentsParser.hpp"

namespace copter::app
{

int CopterApp::Run(int argc, char** argv)
{
    auto arguments = ParseArguments(argc, argv);
    return EXIT_SUCCESS;
}

Arguments CopterApp::ParseArguments(int argc, char** argv) const
{
    ArgumentsParser parser;

    try
    {
        return parser.Parse(argc, argv);
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << std::endl << std::endl;
        std::cerr << parser.GetHelp() << std::endl;
        std::exit(EXIT_FAILURE);
        return {};
    }
}

} // namespace copter::app
