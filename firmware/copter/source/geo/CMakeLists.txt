set(PROJECT_NAME copter-geo)

set(SOURCE_LIST
    Position.hpp
    Position.cpp
    WGS84.hpp
    WGS84.cpp
)

find_package (GeographicLib REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${GeographicLib_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/source"
        ${GeographicLib_INCLUDE_DIRS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
