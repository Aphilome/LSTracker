set(PROJECT_NAME copter-channel)

set(SOURCE_LIST
    IChannel.hpp
    IChannel.cpp
    TCPChannel.hpp
    TCPChannel.cpp
    UARTChannel.hpp
    UARTChannel.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
