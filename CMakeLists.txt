cmake_minimum_required(VERSION 3.28)

find_program(EPITECH_COMPILER NAMES epiclang REQUIRED FALSE)
if(EPITECH_COMPILER)
    set(CMAKE_C_COMPILER ${EPITECH_COMPILER} CACHE FILEPATH "EPITECH epiclang compiler" FORCE)
    message(STATUS "Using EPITECH epiclang: ${EPITECH_COMPILER}")
else()
    message(STATUS "epiclang not found, using default C compiler")
endif()

project(myftp VERSION 1.0
        LANGUAGES C)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(warning_options INTERFACE)

target_compile_options(warning_options INTERFACE -Wall -Wextra -Werror -std=c11)

add_subdirectory(src)
