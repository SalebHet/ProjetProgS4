#include "strategy.h"
#include "grid.h"
#include "afficher.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#define __USE_BSD
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
 /*
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
    }*/

int main (){
    grid g = new_grid();        //Création de la grille de jeu

    grid g = new_grid();        //Cr�ation de la grille de jeu
    strategy strat;
    add_tile(g);                //ajout des 2 premières tuiles pour le jeux
    add_tile(g);
    int i=0;
    while(listNamesStrat[i]!=NULL){
      printf("strat n %d : %s\n",i,listNamesStrat[i]);
      i++;
    }
    printf("Choisissez une strategie a executer : ");
    unsigned int nb_strat;
    do{
      scanf("%d",&nb_strat);
    }while(nb_strat>=i);
    strat=listFunctionsStrat[nb_strat]();

    initscr();
    curs_set(FALSE);
    initscr();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(-1);
    noecho();

    while(!game_over(g)){
      display(g);
      play(g,strat->play_move(NULL,g));
      //usleep(300000);
      //usleep(50000);
    }
    display(g);
    sleep(2);

    endwin();

}
