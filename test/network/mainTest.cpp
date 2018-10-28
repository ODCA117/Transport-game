// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "../catch.hpp"

TEST_CASE( "1: All test cases reside in other .cpp files (empty)", "[multi-file:1]" ) {
}

// ^^^
// Normally no TEST_CASEs in this file.
// Here just to show there are two source files via option --list-tests.

// Compile & run:
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -c 020-TestCase-11.cpp
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -o 020-TestCase TestCase-1.o 020-TestCase-2.cpp && 020-TestCase --success
