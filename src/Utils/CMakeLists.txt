add_library(utils STATIC Options.cpp
        constants.hpp
        Logger.cpp
        Logger.hpp
        StringUtils.cpp)

target_include_directories(utils PUBLIC .
        PUBLIC ${CMAKE_SOURCE_DIR}/src/DesignPattern)

target_link_libraries(utils exceptions)

target_link_libraries(utils warning_options)
