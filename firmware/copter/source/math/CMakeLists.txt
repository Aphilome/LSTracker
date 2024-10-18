set(PROJECT_NAME copter-math)

set(SOURCE_LIST
    Intersection.hpp
    Intersection.cpp
    Point.hpp
    Sphere.hpp
    Utility.cpp
    Utility.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
