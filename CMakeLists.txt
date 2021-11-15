cmake_minimum_required(VERSION 3.16.3)
project(protobuf)

set(CMAKE_CXX_STANDARD 11)


add_compile_options(-L/usr/local/lib)
add_compile_options(-lprotobuf)


add_executable(protobuf-parse main.cpp)
target_link_libraries(protobuf-parse protobuf)