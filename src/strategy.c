#include "strategy.h"

/**
*
* \brief choose the first direction possible in this order: LEFT, DOWN, UP, RIGHT
* \param strategy s, a structure strategy
* \param grid g, the grid
*
**/
static dir FirstStrat(strategy s, grid g) {
    if (can_move(g, LEFT))
        return LEFT;
    if (can_move(g, DOWN))
        return DOWN;
    if (can_move(g, UP))
        return UP;
    else {
        return RIGHT;
    }
}

strategy firstStratConstruct() {
    strategy s = malloc(sizeof(struct strategy_s));
    s->play_move = FirstStrat;
    s->name = "algo du coin groupe H";
    s->mem = NULL;
    s->free_strategy = free_memless_strat;
    return s;
}


strategy(*listFunctionsStrat[])() = {
firstStratConstruct, A2_beziau_pathe_nerestan_efficient,
        A2_beziau_pathe_nerestan_fast, NULL};
char *listNamesStrat[] =
    { "firstStrat", "expected max efficace", "expected max rappide",
NULL };
