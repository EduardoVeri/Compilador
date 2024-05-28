cmake_minimum_required(VERSION 3.10)

set(EXECUTABLE_NAME "compilador")
project(${EXECUTABLE_NAME})

option(SHOW_WARNINGS "Enable or disable compiler warnings" OFF)

set(SRC_DIR "src")
set(INCLUDE_DIR "include")

include_directories(${INCLUDE_DIR})
file(GLOB SOURCES "${SRC_DIR}/*.c")

add_executable(${EXECUTABLE_NAME} ${SOURCES})
        
if(SHOW_WARNINGS)
    target_compile_options(${EXECUTABLE_NAME} PRIVATE   
        # Baseline
        -Wall
        -Wextra # reasonable and standard
        -Wshadow # if a variable declaration shadows one from a parent context
        -Wpedantic # warn if non-standard is used
        # C and C++ Warnings
        -Wunused # warn on anything being unused
        -Wformat=2 # warn on security issues around functions that format output
        -Wcast-align # warn for potential performance problem casts
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        # C++ Warnings
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
    )
else()
    message(STATUS "Compiler warnings disabled")
endif()

# Link the fl library so we can compile the bison .c generated file
target_link_libraries(${EXECUTABLE_NAME} fl)

# Change the output directory of the executable
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Add subdirectory for tests
add_subdirectory(tests)