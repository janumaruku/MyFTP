cmake_minimum_required(VERSION 3.28)
project(myftp VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
