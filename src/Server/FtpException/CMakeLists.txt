add_library(ftp_command_exception STATIC FtpCommandException.cpp
        NoSuchFileOrDirectory.cpp
        PermissionDenied.cpp
        NotADirectory.cpp
        AccessDenied.cpp)

target_include_directories(ftp_command_exception PUBLIC include)

target_link_libraries(ftp_command_exception PUBLIC network server)
