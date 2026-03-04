add_library(exceptions STATIC OptionException.cpp)

target_include_directories(exceptions PUBLIC .)

target_link_libraries(exceptions utils)

target_link_libraries(exceptions warning_options)
