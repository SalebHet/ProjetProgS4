#include "strategy.h"
#include "grid.h"
#include "afficher.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL));  
    initscr();
    curs_set(FALSE);
    initscr();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(-1);
    noecho();
    grid g = new_grid();        //Création de la grille de jeu
    add_tile(g);                //ajout des 2 premières tuiles pour le jeux
    add_tile(g);
    while (!game_over(g)) {     //Boucle jusqu'à la fin de la partie
        afficher(g);            //Affiche la grille à chaque mouvement
        dir d = FirstStrat(g);       //Récupère la direction pour le prochain tour
        if (can_move(g, d)) {   //Vérifie si le mouvement est possible
            play(g, d);
            sleep(2);         //Effectue le mouvement, s'il est possible
        }
    }
    afficher(g);                //Affiche la grille lors du dernier tour
    printw("game over \n");     //Affiche que la partie est terminée
    delete_grid(g);             //Supprime la grille
    endwin();
    refresh();
    return EXIT_SUCCESS;
}
