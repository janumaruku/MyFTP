include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

option(WITH_COVERAGE "Enable coverage reporting" OFF)

add_executable(
        unit_tests
        hello_test.cpp
)
target_link_libraries(
        unit_tests
        GTest::gtest_main
)

set_target_properties(hello_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(hello_test)
