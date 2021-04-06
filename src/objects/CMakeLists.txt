cmake_minimum_required(VERSION 3.10.2)

project(GraphicsEngine  VERSION 1.0
                        DESCRIPTION "Ray Tracing Graphics Engine"
                        LANGUAGES CXX)

set(object_files Object.cpp Plane.cpp Sphere.cpp Triangle.cpp Mesh.cpp XYRectangle.cpp)
add_library(objects ${object_files})
