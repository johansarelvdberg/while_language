﻿# CMakeList.txt : CMake project for While Language, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("While Language")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
# Add source to this project's executable.
add_executable (CMakeTarget "src/lex_analise.cpp" "src/main.cpp" "include/error.h" "include/identifiers.h" "src/error.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.