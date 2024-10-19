#include "UARTChannel.hpp"

#include <cassert>
#include <execution>

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h> 

namespace
{

int OpenUART(const std::string& device)
{
    int fd = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        throw std::runtime_error("Failed to open UART");
    }
    fcntl(fd, F_SETFL, 0);
    return fd;
}

int GetBaud(std::uint32_t baudrate)
{
    switch (baudrate)
    {
        case 1200:    return B1200;
        case 1800:    return B1800;
        case 9600:    return B9600;
        case 19200:   return B19200;
        case 38400:   return B38400;
        case 57600:   return B57600;
        case 115200:  return B115200;
        case 230400:  return B230400;
        case 460800:  return B460800;
        case 500000:  return B500000;
        case 576000:  return B576000;
        case 921600:  return B921600;
        case 1000000: return B1000000;
        case 1152000: return B1152000;
        case 1500000: return B1500000;
        case 2000000: return B2000000;
        case 2500000: return B2500000;
        case 3000000: return B3000000;
        case 3500000: return B3500000;
        case 4000000: return B4000000;
        default:      return -1;
    }
}

void ConfigureUART(int fd, std::uint32_t baudrate)
{
    if (!isatty(fd))
    {
        throw std::invalid_argument("fd");
    }

    termios config;
    if (tcgetattr(fd, &config) < 0)
    {
        throw std::runtime_error("Failed to get config for UART");
    }

    config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
    config.c_oflag &= ~(OCRNL | ONLCR | ONLRET | ONOCR | OFILL | OPOST);
    config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    config.c_cflag &= ~(CSIZE | PARENB);
    config.c_cflag |= CS8;

    config.c_cc[VMIN]  = 1;
    config.c_cc[VTIME] = 10;

    auto baud = GetBaud(baudrate);
    if (cfsetispeed(&config, baud) < 0)
    {
        throw std::runtime_error("Failed to set input speed for UART");
    }
    if (cfsetospeed(&config, baud) < 0)
    {
        throw std::runtime_error("Failed to set OUTPUT speed for UART");
    }

    if (tcsetattr(fd, TCSAFLUSH, &config) < 0)
    {
        throw std::runtime_error("Failed to set config for UART");
    }
}

} // namespace

namespace copter::channel
{

UARTChannel::UARTChannel(const std::string& device, std::uint32_t baudrate)
    : m_file(OpenUART(device))
{
    ConfigureUART(m_file, baudrate);
}

UARTChannel::~UARTChannel()
{
    int result = close(m_file);
    assert(result == 0);
}

std::size_t UARTChannel::Read(void* data, std::size_t length)
{
    return read(m_file, data, length);
}

std::size_t UARTChannel::Write(const void* data, std::size_t length)
{
    auto bytes_written = write(m_file, data, length);
    tcdrain(m_file);
    return bytes_written;
}

} // namespace copter::channel
