cmake_minimum_required(VERSION 3.10)

# Enable testing
enable_testing()

# Set CMocka include and library directories
find_path(CMOCKA_INCLUDE_DIR NAMES cmocka.h)
find_library(CMOCKA_LIBRARY NAMES cmocka)

if (NOT CMOCKA_INCLUDE_DIR OR NOT CMOCKA_LIBRARY)
    message(FATAL_ERROR "Could not find CMocka. Please set CMOCKA_INCLUDE_DIR and CMOCKA_LIBRARY.")
    return()
else()
    message(STATUS "Found CMocka: ${CMOCKA_INCLUDE_DIR}, ${CMOCKA_LIBRARY}")
endif()

include_directories(${CMOCKA_INCLUDE_DIR})

# Define the source files for the tests
file(GLOB TEST_SOURCES "*.c")

# Add an executable for the tests
add_executable(runTests ${TEST_SOURCES})

# Link the test executable with CMocka
target_link_libraries(runTests ${CMOCKA_LIBRARY})

# Add the tests
add_test(NAME runTests COMMAND runTests)

add_custom_target(runTestsTarget
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS runTests
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
)