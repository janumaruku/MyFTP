add_library(server STATIC Server.cpp
        HelpOptionHandler.cpp
        HelpOptionHandler.hpp)

target_include_directories(server PUBLIC .
        PUBLIC ${CMAKE_SOURCE_DIR}/src/DesignPattern)

target_link_libraries(server warning_options)
