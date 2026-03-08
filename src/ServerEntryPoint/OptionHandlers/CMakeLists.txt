add_library(option_handlers STATIC HelpOptionHandler.cpp
        PortOptionHandler.cpp
        DirectoryOptionHandler.cpp
        include/DirectoryOptionHandler.hpp)

target_include_directories(option_handlers PUBLIC include ..)

#target_link_libraries(option_handlers server)

target_link_libraries(option_handlers utils warning_options)
