cmake_minimum_required(VERSION 3.15)

project(raytracing VERSION 0.1)

set(cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1)

add_executable(raytracing main.cpp vec3.h color.h ray.h commonheader.h interval.h)
