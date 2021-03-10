cmake_minimum_required(VERSION 3.10.2)

project(GraphicsEngine  VERSION 1.0
                        DESCRIPTION "Ray Tracing Graphics Engine"
                        LANGUAGES CXX)

set(image_files Image.cpp)
add_library(image ${image_files})

# target_link_libraries(image lights)
