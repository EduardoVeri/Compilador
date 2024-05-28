cmake_minimum_required(VERSION 3.10)

# Enable testing
enable_testing()

# Find CMocka package
find_package(CMocka REQUIRED)

# Define the source files for the tests
file(GLOB TEST_SOURCES "*.c")

# Add an executable for the tests
add_executable(runTests ${TEST_SOURCES})

# Link the test executable with CMocka
target_link_libraries(runTests cmocka)

# Add the tests
add_test(NAME runTests COMMAND runTests)
