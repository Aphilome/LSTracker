set(PROJECT_NAME copter-tracker)

set(SOURCE_LIST
    LocalPositionSystem.hpp
    LocalPositionSystem.cpp
    Position.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
