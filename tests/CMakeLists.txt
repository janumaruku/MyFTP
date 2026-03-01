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

target_compile_options(unit_tests PRIVATE --coverage -O0 -g)
target_link_options(unit_tests PRIVATE --coverage)

# Detect matching LLVM coverage tools
find_program(LLVM_PROFDATA NAMES llvm-profdata-18)
find_program(LLVM_COV NAMES llvm-cov-18)

if(NOT LLVM_PROFDATA OR NOT LLVM_COV)
    message(FATAL_ERROR "LLVM 18 coverage tools not found")
endif()

if (WITH_COVERAGE)

    # Where profile data will be written
    set(COVERAGE_RAW_FILE ${CMAKE_BINARY_DIR}/default.profraw)
    set(COVERAGE_DATA_FILE ${CMAKE_BINARY_DIR}/default.profdata)
    set(COVERAGE_HTML_DIR ${CMAKE_BINARY_DIR}/coverage_html)

    # Ensure tests write profile data to predictable location
    add_custom_target(run_tests_with_coverage
            COMMAND ${CMAKE_COMMAND} -E env
            LLVM_PROFILE_FILE=${COVERAGE_RAW_FILE}
            $<TARGET_FILE:unit_tests>
            DEPENDS unit_tests
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    # Merge raw profile into profdata
    add_custom_target(merge_coverage
            COMMAND ${LLVM_PROFDATA} merge -sparse
            ${COVERAGE_RAW_FILE}
            -o ${COVERAGE_DATA_FILE}
            DEPENDS run_tests_with_coverage
    )

    # Generate terminal report
    add_custom_target(coverage_report
            COMMAND ${LLVM_COV} report
            $<TARGET_FILE:unit_tests>
            -instr-profile=${COVERAGE_DATA_FILE}
            -ignore-filename-regex='build/_deps'
            DEPENDS merge_coverage
    )

    # Generate HTML report
    add_custom_target(coverage_html
            COMMAND ${LLVM_COV} show
            $<TARGET_FILE:unit_tests>
            -instr-profile=${COVERAGE_DATA_FILE}
            -format=html
            -output-dir=${COVERAGE_HTML_DIR}
            -ignore-filename-regex='build/_deps'
            DEPENDS merge_coverage
    )

    # Master target
    add_custom_target(coverage
            DEPENDS coverage_report coverage_html
    )

endif()

include(GoogleTest)
gtest_discover_tests(unit_tests)
