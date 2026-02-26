cmake_minimum_required(VERSION 3.28)

project(myftp VERSION 1.0
        LANGUAGES CXX)

find_program(EPITECH_COMPILER NAMES epiclang REQUIRED FALSE)
if(EPITECH_COMPILER)
    set(CMAKE_C_COMPILER ${EPITECH_COMPILER} CACHE FILEPATH "EPITECH epiclang compiler" FORCE)
    message(STATUS "Using EPITECH epiclang: ${EPITECH_COMPILER}")
else()
    message(STATUS "epiclang not found, using default C compiler")
endif()

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
set(CMAKE_C_FLAGS "--coverage" CACHE STRING "C flags" FORCE)
set(CMAKE_CXX_FLAGS "--coverage" CACHE STRING "CXX flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "--coverage" CACHE STRING "Linker flags" FORCE)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands" FORCE)


add_library(warning_options INTERFACE)

target_compile_options(warning_options INTERFACE -Wall -Wextra #[[-Werror]])

add_subdirectory(src)

enable_testing()

add_subdirectory(tests)
