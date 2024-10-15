set(PROJECT_NAME copter)

set(SOURCE_LIST Main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
