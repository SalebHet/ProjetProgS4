cmake_minimum_required(VERSION 2.6)
project(2048)

add_definitions(-std=c99 -Wall -Werror)

add_executable(test-grid test.c grid.c afficher.c)
add_executable(2048 main.c grid.c afficher.c)

target_link_libraries(test-grid ncurses m)
target_link_libraries(2048 ncurses m)