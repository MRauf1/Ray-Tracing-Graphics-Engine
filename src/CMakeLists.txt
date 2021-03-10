cmake_minimum_required(VERSION 3.10.2)

project(GraphicsEngine  VERSION 1.0
                        DESCRIPTION "Ray Tracing Graphics Engine"
                        LANGUAGES CXX)

add_subdirectory(math/)
add_subdirectory(image/)
add_subdirectory(lights/)
add_subdirectory(objects/)

set(src_files main.cpp World.cpp Camera.cpp)
add_executable(main ${src_files})

target_link_libraries(main math image lights objects)
