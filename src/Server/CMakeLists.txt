add_subdirectory(FtpProtocol)

add_library(server STATIC Server.cpp
        ClientSession.cpp)

target_include_directories(server PUBLIC include)

target_link_libraries(server utils network ftp_protocol)

target_link_libraries(server warning_options)
