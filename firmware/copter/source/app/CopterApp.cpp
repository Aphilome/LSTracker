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
    communicator.SetGlobalPositionCallback([](const communicator::GlobalPositionInfo& gpi)
    {
        std::cout
            << "[GlobalPositionInfo]"
            << " time_boot = " << gpi.time_boot_ms
            << "; latitude = " << gpi.latitude_deg
            << "; longitude = " << gpi.longitude_deg
            << "; altitude = " << gpi.altitude_m
            << "; relative_altitude = " << gpi.relative_altitude_m
            << "; speed_x = " << gpi.speed_x_ms
            << "; speed_y = " << gpi.speed_y_ms
            << "; speed_z = " << gpi.speed_z_ms
            << "; yaw = " << gpi.yaw_deg
            << std::endl;
    });
    /*communicator.SetGPSRawCallback([](const communicator::GPSRawInfo& gri)
    {
        std::cout
            << "[GPSRawInfo]"
            << " time = " << gri.time_us
            << "; latitude = " << gri.latitude_deg
            << "; longitude = " << gri.longitude_deg
            << "; altitude = " << gri.altitude_m
            << std::endl;
    });*/

    while (true)
    {
    }

    return EXIT_SUCCESS;
}

std::optional<Arguments> CopterApp::ParseArguments(int argc, char** argv) const
{
    ArgumentsParser parser;

    try
    {
        return parser.Parse(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl << std::endl;
        std::cerr << parser.GetHelp() << std::endl;
        return std::nullopt;
    }
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
