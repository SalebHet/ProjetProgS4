#include "strategy.h"
#include "grid.h"
#include "afficher.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

/*
struct strategy_s
{
  void* mem;  Points the the data stored by the strategy.
  char* name; The strategy's name. This will be used to display the tournament scores.
  dir (*play_move) (strategy, grid); A function which returns the direction chosen by the strategy.
    The first parameter is a pointer to the current strategy (useless for memoryless strategies). The second one is the current grid.
  void (*free_strategy) (strategy); Frees any resources allocated during the strategy's creation (<name>, <mem>, ...).
};
*/

static int getStrat() {              //Fonction permettant de récupérer une touche du clavier et d'y associer une stratégie
    while (true) {
        int c = getch();
        if (c != ERR) {
            switch (c) {
            case KEY_1:
                return 1;
            case KEY_2:
                return 2;

            }
        }
    }
}

int main (){
     initscr();
    curs_set(FALSE);
    initscr();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(-1);
    noecho();
    grid g = new_grid();        //Création de la grille de jeu
    strategy_s strat = new strategy_s;
    add_tile(g);                //ajout des 2 premières tuiles pour le jeux
    add_tile(g);
    int nb_strat = getStrat();
    switch (nb_strat){
    case 1:
        strat -> name = new_char "Strategie Rapide";
        strat -> (*play_move)
    }


}
