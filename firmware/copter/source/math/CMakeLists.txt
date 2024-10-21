set(PROJECT_NAME copter-math)

set(SOURCE_LIST
    Intersection.hpp
    Intersection.cpp
    Point.hpp
    Point.cpp
    Sphere.hpp
    Sphere.cpp
    Triangle.hpp
    Triangle.cpp
    Vector.hpp
    Vector.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
