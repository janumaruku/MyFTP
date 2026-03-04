add_executable(myftp ServerEntryPoint.cpp main.cpp)

target_include_directories(myftp PUBLIC .)

target_link_libraries(myftp server
        utils
        design_pattern
        option_handlers
        warning_options)

set_target_properties(myftp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
