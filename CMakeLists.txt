cmake_minimum_required(VERSION 3.15)

project(raytracing VERSION 0.1)

set(header_dir "${PROJECT_HEADER_DIR}/src/")

file (GLOB header_files "${header_dir}/*.h")

add_executable(raytracing main.cpp ${header_files})
