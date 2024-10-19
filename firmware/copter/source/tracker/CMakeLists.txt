set(PROJECT_NAME copter-tracker)

set(SOURCE_LIST
    LocalPositionSystem.hpp
    LocalPositionSystem.cpp
    TriangulationAlgorithm.hpp
    TriangulationAlgorithm.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        copter-geo
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/source"
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
