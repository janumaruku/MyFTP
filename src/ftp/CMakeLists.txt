add_executable(myftp main.c)

target_link_libraries(myftp PRIVATE warning_options)

set_target_properties(myftp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
