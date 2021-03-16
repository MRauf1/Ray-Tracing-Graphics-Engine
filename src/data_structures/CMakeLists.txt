cmake_minimum_required(VERSION 3.10.2)

project(GraphicsEngine  VERSION 1.0
                        DESCRIPTION "Ray Tracing Graphics Engine"
                        LANGUAGES CXX)

set(data_structures_files AABB.cpp)
add_library(data_structures ${data_structures_files})

# target_link_libraries(lights objects)
