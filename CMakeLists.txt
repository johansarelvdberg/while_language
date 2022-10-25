# CMakeList.txt : CMake project for While Language, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("While Language")

#set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/deps/boost)
#find_package(Boost REQUIRED)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/test
)


#include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIRS})


add_library(OWN_LIB 
"src/lex/lex_analise.cpp" 
"include/error.h" 
"include/identifiers.h" 
"src/error.cpp"
"include/syntax/syntax.h" 
"include/concepts.h" 
"include/lex/NextElement.h" 
"src/lex/NextElement.cpp" 
"include/syntax/Node.h" 
"include/syntax/statement.h" 
"include/syntax/expression.h" 
"include/syntax/predicates.h" 
"src/syntax/syntax.cpp" 
"src/syntax/predicates.cpp" 
"src/syntax/expression.cpp" 
"include/syntax/structure.h"
"src/syntax/structure.cpp"  
"src/syntax/statement.cpp" 
"include/syntax/format.h" 
)
set_property(TARGET OWN_LIB PROPERTY CXX_STANDARD 23)


# Add source to this project's executable.
add_executable (CMakeTarget "src/main.cpp")
target_link_libraries(CMakeTarget PRIVATE OWN_LIB)
set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 23)


# TODO: Add tests and install targets if needed.


add_executable(test_while_basic "test/test_while_basic.cpp")
target_link_libraries(test_while_basic PRIVATE OWN_LIB)
set_property(TARGET test_while_basic PROPERTY CXX_STANDARD 23)

add_executable(test_if_basic "test/test_if_basic.cpp")
target_link_libraries(test_if_basic PRIVATE OWN_LIB)
set_property(TARGET test_if_basic PROPERTY CXX_STANDARD 23)

enable_testing()
add_test(Test1 test_while_basic)
add_test(Test2 test_if_basic)

