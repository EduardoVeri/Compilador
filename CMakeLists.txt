cmake_minimum_required(VERSION 3.10)

set(EXECUTABLE_NAME "compilador")
project(${EXECUTABLE_NAME})

set(SRC_DIR "src")
set(INCLUDE_DIR, "include")

option(SHOW_WARNINGS "Enable or disable compiler warnings" OFF)

# Define an option to enable or disable generating lexer and parser files
option(GENERATE_LEXER_PARSER "Generate lexer and parser files using Flex and Bison" OFF)

include_directories(${INCLUDE_DIR})
file(GLOB SOURCES ${SRC_FOLDER}"/*.c")

add_executable(${EXECUTABLE_NAME} ${SOURCES})

if(GENERATE_LEXER_PARSER)
# Add custom commands to generate lexer and parser files
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/parser.c ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/parser.h
        COMMAND bison -d -o${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/parser.c ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/parser.y
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/parser.y
        COMMENT "Generating parser.c and parser.h with Bison"
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/lexer.c
        COMMAND flex -o${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/lexer.c ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/lexer.l
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/lexer.l
        COMMENT "Generating lexer.c with Flex"
        )
        
        # Add custom target to depend on generated files
    add_custom_target(generate_lexer_parser
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/parser.c ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/parser.h ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/lexer.c
    )
        
    # Add the generated files to the list of sources
    list(APPEND SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/parser.c ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/lexer.c)
    
    # Ensure the executable depends on the generate_lexer_parser target
    add_dependencies(${EXECUTABLE_NAME} generate_lexer_parser)
endif()
        
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
        -Wnon-virtual-dtor # if a class with virtual func has a non-virtual dest
        -Wold-style-cast # warn for c-style casts
        -Woverloaded-virtual # if you overload (not override) a virtual function
        -Weffc++ # violations from Scott Meyers’ Effective C++
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
    )
else()
    message(STATUS "Compiler warnings disabled")
endif()

# Link the fl library so we can compile the bison .c generated file
target_link_libraries(${EXECUTABLE_NAME} fl)


