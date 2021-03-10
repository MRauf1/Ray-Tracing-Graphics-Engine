cmake_minimum_required(VERSION 3.10.2)

project(EngineTest  VERSION 1.0
                    DESCRIPTION "Graphics Engine Test"
                    LANGUAGES CXX)

set(test_objects_files  ../../src/objects/Object.cpp ../../src/objects/Plane.cpp
                        ../../src/objects/Sphere.cpp ../../src/objects/Triangle.cpp
                        Plane_test.cpp Sphere_test.cpp Triangle_test.cpp)
add_library(test_objects ${test_objects_files})
