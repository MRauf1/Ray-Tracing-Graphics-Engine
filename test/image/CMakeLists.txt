cmake_minimum_required(VERSION 3.10.2)

project(EngineTest  VERSION 1.0
                    DESCRIPTION "Graphics Engine Test"
                    LANGUAGES CXX)

set(test_image_files    ../../src/image/Image.cpp)
add_library(test_image ${test_image_files})
