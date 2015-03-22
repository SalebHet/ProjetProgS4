cmake_minimum_required(VERSION 2.6)
project(2048)

add_definitions(-std=c99 -Wall -Werror)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/)
message(${CMAKE_HOME_DIRECTORY})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)
include_directories(include)
add_subdirectory(src)

