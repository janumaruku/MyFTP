add_library(design_pattern STATIC FactoryTemplate.cpp)

target_include_directories(design_pattern PUBLIC .)

target_link_libraries(design_pattern warning_options)
