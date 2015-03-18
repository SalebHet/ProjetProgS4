#include "afficher.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

dir getDir(){  //Fonction permettant de récupérer une touche du clavier et d'y associer une direction
  while(true){
  char c = getchar();

    switch(c){
        case 'z':
            return UP;
        case 'q':
            return LEFT;
        case 's':
            return DOWN;
        case 'd':
            return RIGHT;

    }
  }
}

int main(){
    initscr();
    grid g = new_grid(); //Création de la grille de jeu
    add_tile(g); //ajout des 2 première tiles pour le jeux
    add_tile(g);
    printw("z, q, s ou d et 'entree' pour faire un mouvement\n");
    while(!game_over(g)){ //Boucle jusqu'à la fin de la partie
        afficher(g); //Affiche la grille à chaque mouvement
        dir d = getDir(); //Récupère la direction pour le prochain tour
        if(can_move(g,d)){ //Vérifie si le mouvement est possible
	  play(g,d); //Effectue le mouvement si le mouvement est possible

	}
	else
	  printw("mouvement impossible\n"); //Indique que le mouvement n'est pas possible
    }
    afficher(g); //Affiche la grid lors du dernier tour
    printw("game over \n"); //Affiche que la partie est terminer
    delete_grid(g); //Supprime la Grid
    endwin();
    refresh();
    return EXIT_SUCCESS;
}
