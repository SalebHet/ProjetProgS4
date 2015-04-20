add_library(grid grid.c)
add_library(strategy SHARED strategy.c)
add_library(A2_beziau_pathe_nerestan_efficient SHARED strategyLib.c)
add_library(A2_beziau_pathe_nerestan_fast SHARED strategyLib.c)

add_executable(test-grid test.c afficher.c)
add_executable(2048 main.c afficher.c keyboard.c)
add_executable(2048-gui 2048-gui.c)
add_executable(stratMain stratmain.c grid.c afficher.c)

target_compile_definitions(A2_beziau_pathe_nerestan_efficient PRIVATE DEPTH=3 STRAT_NAME="efficient algo groupe H" 
  NAME=A2_beziau_pathe_nerestan_efficient)
target_compile_definitions(A2_beziau_pathe_nerestan_fast PRIVATE DEPTH=2 STRAT_NAME="fast algo groupe H" 
  NAME=A2_beziau_pathe_nerestan_fast)

target_link_libraries(test-grid strategy ncurses grid m)
target_link_libraries(strategy A2_beziau_pathe_nerestan_efficient A2_beziau_pathe_nerestan_fast m)
target_link_libraries(2048 ncurses grid m)
target_link_libraries(stratMain strategy ncurses grid m)
target_link_libraries(2048-gui SDL_ttf SDL_mixer SDLmain SDL grid m)
target_link_libraries(A2_beziau_pathe_nerestan_fast m)
target_link_libraries(A2_beziau_pathe_nerestan_efficient m)