#include <IChannel.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    auto channel = copter::channel::Open(copter::channel::Protocol::TCP, "127.0.0.1:50000");

    return 0;
}
