set(PROJECT_NAME copter-app)

set(SOURCE_LIST
    Main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        copter-channel
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/source/channel/"
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
