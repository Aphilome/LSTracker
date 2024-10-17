set(PROJECT_NAME copter-channel)

set(SOURCE_LIST
    IChannel.hpp
    IChannel.cpp
    TCPChannel.hpp
    TCPChannel.cpp
    UDPChannel.hpp
    UDPChannel.cpp
    UARTChannel.hpp
    UARTChannel.cpp
)

find_package(sockpp REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Sockpp::sockpp-static
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
