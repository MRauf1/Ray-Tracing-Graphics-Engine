cmake_minimum_required(VERSION 3.10.2)

project(EngineTest  VERSION 1.0
                    DESCRIPTION "Graphics Engine Test"
                    LANGUAGES CXX)

# set(test_math_files ../../src/math/Vec3.cpp ../../src/math/Ray.cpp
#                     Vec3_test.cpp Ray_test.cpp)
# add_library(test_math ${test_math_files})

set(test_math_files ../src/math/Vec3.cpp ../src/math/Ray.cpp
                    math/Vec3_test.cpp math/Ray_test.cpp PARENT_SCOPE)
