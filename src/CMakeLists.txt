add_library(grid grid.c)

add_executable(test-grid test.c afficher.c strategy.c)
add_executable(2048 main.c afficher.c)
add_executable(Afficher_Strategy StrategyGrap.c afficher.c strategy.c)
add_executable(stratMain stratmain.c strategy.c grid.c afficher.c)

target_link_libraries(test-grid ncurses  grid m)
target_link_libraries(2048 ncurses grid m)
target_link_libraries(Afficher_Strategy ncurses grid m)
target_link_libraries(stratMain ncurses grid m)