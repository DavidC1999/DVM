cmake_minimum_required(VERSION 3.19)
project(VM)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -static-libstdc++ -static-libgcc -Wall -Wextra -pedantic -Werror")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    string(CONCAT CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -g -DDEBUG")
else()
    string(CONCAT CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -O2")
endif()

message("C++ FLAGS:")
message(${CMAKE_CXX_FLAGS})

include(${CMAKE_CURRENT_SOURCE_DIR}/VM/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/assembler/CMakeLists.txt)
