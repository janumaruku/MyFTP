add_library(network Acceptor.cpp
        ConnectedSocket.cpp
        Endpoint.cpp
        ErrorCode.cpp
        IoContext.cpp
        ListeningSocket.cpp)

target_include_directories(network PUBLIC include)

target_link_libraries(network utils warning_options)
