add_library(server STATIC Server.cpp
        LinteningSocket.cpp
        ListeningSocket.hpp
        Acceptor.cpp
        Acceptor.hpp
        Endpoint.cpp
        Endpoint.hpp
        IoContext.cpp
        IoContext.hpp
        ErrorCode.cpp
        ErrorCode.hpp
        ConnectedSocket.cpp
        ConnectedSocket.hpp)

target_include_directories(server PUBLIC .
        PUBLIC ${CMAKE_SOURCE_DIR}/src/DesignPattern)

target_link_libraries(server utils)

target_link_libraries(server warning_options)
