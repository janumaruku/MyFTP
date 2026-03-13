add_subdirectory(FtpException)

add_subdirectory(FtpProtocol)

add_library(server STATIC Server.cpp
        ClientSession.cpp
        FtpException/FtpCommandException.cpp
        FtpException/include/FtpCommandException.hpp)

target_include_directories(server PUBLIC include)

target_link_libraries(server PUBLIC utils
        PUBLIC network
        PUBLIC ftp_protocol
        PUBLIC ftp_command_exception
        warning_options)

#target_link_libraries(server )
