cmake_minimum_required(VERSION 3.27)
project(Calculator_original)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(.)
include_directories(include)
include_directories(include/calc)

add_library(calc
        src/Calculator.cpp
        include/calc/Calculator.h
        include/calc/Lexer.h
        src/Lexer.cpp
        include/calc/Parser.h
        src/Parser.cpp
)
target_include_directories(calc PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)


if (MSVC)
    target_compile_options(calc PRIVATE /W4 /permissive-)
else()
    target_compile_options(calc PRIVATE -Wall -Wextra -Wpedantic)
endif()