add_library(utils STATIC Options.cpp
        Logger.cpp
        StringUtils.cpp
        OptionException.cpp)

target_include_directories(utils PUBLIC include)

target_link_libraries(utils design_pattern)

target_link_libraries(utils warning_options)
