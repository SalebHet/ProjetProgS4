cmake_minimum_required(VERSION 2.6)
project(2048)

add_definitions(-std=c99 -Wall -Werror)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)

include_directories(include)

add_subdirectory(src)

