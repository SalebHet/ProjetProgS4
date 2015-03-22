#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#include "afficher.h"

static char* itoa(int i);
static void afficherLigne();
/**
 * \brief turns an int into a 6 sized string
 * \pre the number must be lower or equal to one million in base 10.
 */
static char* itoa(int i){
  char* ret=malloc(7*sizeof(char)); //Alloue l'espace m�moire permettant de stocker une chaine de 7 charact�res. (dont le 0 final)
  char* copie=ret+5;//Le bit de poid faible est � droite donc on commence par la droite
  memset(ret,' ',6);//On met un espace dans les 6 premiers caract�res
  while(i!=0){
    *copie=(i%10)+48;//Le 0 est cod� par le nombre 48, le 1 par 49, etc...
    copie--;//on passe au caract�re � gauche
    i/=10;
  }
  ret[6]='\0';//on met un 0 dans le 7eme caract�re
  return ret;
}

/**
 * \brief display a line of GRID_SIZE times the size of a tile (left or up side)
 * \pre the window must be large enough to display the grid
 */
static void afficherLigne(){ //Fonction permettant d'afficher une ligne horizontale � la taille de la grille
  printw("+");
  for(int i=0;i<GRID_SIDE;i++)
    printw("------+");
  printw("\n");
}

void afficher(grid g){
  erase();//on efface la fenetre
  afficherLigne();
  char *nb;
  int val;
  for(int j=0;j<GRID_SIDE;j++){
    for(int i=0;i<GRID_SIDE;i++){
      val=get_tile(g,i,j);
      if(val!=0)
	val=pow(2,val); //Transforme la valeur logarithmique en valeur d�cimale
      nb=itoa(val);
      printw("|%s",nb);
      free(nb); //Lib�re la m�moire employ�e par la chaine de charact�re
    }
    printw("|\n");
    afficherLigne();
  }
  printw("Score: %ld \n",grid_score(g));
  refresh();//on actualise l'affichage de la fenetre

}

