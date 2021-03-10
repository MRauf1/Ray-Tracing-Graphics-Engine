cmake_minimum_required(VERSION 3.10.2)

project(GraphicsEngine  VERSION 1.0
                        DESCRIPTION "Ray Tracing Graphics Engine"
                        LANGUAGES CXX)

set(math_files Vec3.cpp Ray.cpp)
add_library(math ${math_files})

# target_link_libraries(math image)
