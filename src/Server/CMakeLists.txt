add_library(server STATIC Server.cpp
        ClientSession.cpp)

target_include_directories(server PUBLIC include)

target_link_libraries(server utils network)

target_link_libraries(server warning_options)
