cmake_minimum_required(VERSION 3.10.2)

project(EngineTest  VERSION 1.0
                    DESCRIPTION "Graphics Engine Test"
                    LANGUAGES CXX)

add_subdirectory(math/)
add_subdirectory(image/)
add_subdirectory(lights/)
add_subdirectory(objects/)

set(test_src_files  main.cpp ../../src/World.cpp ../../src/Camera.cpp
                    World_test.cpp Camera_test.cpp)
add_executable(test_main    ${test_src_files} ${test_math_files} ${test_image_files}
                            ${test_lights_files} ${test_objects_files})

# target_link_libraries(test_main test_math test_image test_lights test_objects)
