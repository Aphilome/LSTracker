set(PROJECT_NAME copter-app)

set(SOURCE_LIST
    Main.cpp
    ArgumentsParser.hpp
    ArgumentsParser.cpp
    CopterApp.hpp
    CopterApp.cpp
)

find_package(argparse REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        copter-channel
        copter-communicator
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/source"
        "${argparse_DIR}/../../include"
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
