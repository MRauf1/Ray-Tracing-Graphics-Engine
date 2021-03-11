cmake_minimum_required(VERSION 3.10.2)

project(EngineTest  VERSION 1.0
                    DESCRIPTION "Graphics Engine Test"
                    LANGUAGES CXX)

# set(test_lights_files    ../../src/lights/PointLight.cpp)
# add_library(test_lights ${test_lights_files})

set(test_lights_files ../src/lights/PointLight.cpp PARENT_SCOPE)
