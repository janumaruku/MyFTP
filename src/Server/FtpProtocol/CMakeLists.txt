add_library(ftp_protocol STATIC FtpProtocol.cpp
        IFtpCommand.cpp
        UserCommand.cpp
        QuitCommand.cpp
        PassCommand.cpp
        PwdCommand.cpp
        CwdCommand.cpp)

target_include_directories(ftp_protocol PUBLIC include)

target_link_libraries(ftp_protocol PUBLIC network server)
