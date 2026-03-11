add_library(ftp_protocol STATIC FtpProtocol.cpp
        IFtpCommand.cpp
        UserCommand.cpp)

target_include_directories(ftp_protocol PUBLIC include)

target_link_libraries(ftp_protocol PUBLIC network server)
