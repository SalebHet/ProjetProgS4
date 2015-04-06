add_library(grid grid.c)
add_library(strategy SHARED strategy.c)

add_executable(test-grid test.c afficher.c)
add_executable(2048 main.c afficher.c)
add_executable(stratMain stratmain.c grid.c afficher.c)

target_link_libraries(test-grid strategy ncurses grid m)
target_link_libraries(2048 ncurses grid m)
target_link_libraries(stratMain strategy ncurses grid m)