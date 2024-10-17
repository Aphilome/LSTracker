set(PROJECT_NAME copter-communicator)

set(SOURCE_LIST
    ByteStream.hpp
    ByteStream.cpp
    GlobalPositionInfo.hpp
    GlobalPositionInfo.cpp
    MAVLinkCommunicator.hpp
    MAVLinkCommunicator.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        copter-channel
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/source"
        "${PROJECT_SOURCE_DIR}/external/mavlink_v2"
)

target_compile_options(${PROJECT_NAME} PRIVATE "-Wno-address-of-packed-member")

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
