cmake_minimum_required(VERSION 3.9.1)
project(Transfer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

file(GLOB network_SRC
  "src/network/*.cpp"
  "test/network/*.h"
)
file(GLOB test_SRC
  "test/network/*.cpp"
)

#build library
add_library(network SHARED ${network_SRC})

#build tests
find_package(Catch2 REQUIRED)

add_executable(testlib ${test_SRC} ${network_SRC})
target_link_libraries(testlib Catch2::Catch2)


add_executable(transfer src/app.cpp)
target_link_libraries(transfer network)
