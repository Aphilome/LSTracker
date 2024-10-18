set(PROJECT_NAME copter-geo)

set(SOURCE_LIST
    Position.hpp
    WGS84.hpp
    WGS84.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
