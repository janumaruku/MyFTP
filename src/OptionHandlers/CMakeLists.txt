add_library(option_handlers STATIC HelpOptionHandler.cpp
        PortOptionHandler.cpp
        AddressOptionHandler.cpp
        AddressOptionHandler.hpp)

target_include_directories(option_handlers PUBLIC .)

target_link_libraries(option_handlers exceptions server)

target_link_libraries(option_handlers warning_options)
