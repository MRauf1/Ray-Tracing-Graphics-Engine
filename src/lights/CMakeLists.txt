cmake_minimum_required(VERSION 3.10.2)

project(GraphicsEngine  VERSION 1.0
                        DESCRIPTION "Ray Tracing Graphics Engine"
                        LANGUAGES CXX)

set(lights_files PointLight.cpp XYRectangleLight.cpp)
add_library(lights ${lights_files})

# target_link_libraries(lights objects)
