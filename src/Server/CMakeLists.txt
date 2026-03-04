add_library(server STATIC Server.cpp)

target_include_directories(server PUBLIC .
        PUBLIC ${CMAKE_SOURCE_DIR}/src/DesignPattern)

target_link_libraries(server utils)

target_link_libraries(server warning_options)
