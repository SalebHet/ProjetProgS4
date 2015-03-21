#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#include "afficher.h"

static char* itoa(int i);
static void afficherLigne();
/**
 * \brief transforme un int en chaine de caractère de taille 6 (plus le 0 final)
 * \pre la taille du nombre en base 10 doit etre inférieur ou égal à 6 chiffres
 */
static char* itoa(int i){
  char* ret=malloc(7*sizeof(char)); //Alloue l'espace mémoire permettant de stocker une chaine de 7 charactères. (dont le 0 final)
  char* copie=ret+5;//Le bit de poid faible est à droite donc on commence par la droite
  memset(ret,' ',6);//On met un espace dans les 6 premiers caractères
  while(i!=0){
    *copie=(i%10)+48;//Le 0 est codé par le nombre 48, le 1 par 49, etc...
    copie--;//on passe au caractère à gauche
    i/=10;
  }
  ret[6]='\0';//on met un 0 dans le 7eme caractère
  return ret;
}

/**
 * \brief affiche une ligne contenant GRID_SIDE fois le coté supérieur (ou inférieur) des tuiles 
 * \pre la taille du terminal doit etre sufisant pour afficher une largeur de grille
 */
static void afficherLigne(){ //Fonction permettant d'afficher une ligne horizontale à la taille de la grille
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
	val=pow(2,val); //Transforme la valeur logarithmique en valeur décimale
      nb=itoa(val);
      printw("|%s",nb);
      free(nb); //Libère la mémoire employée par la chaine de charactère
    }
    printw("|\n");
    afficherLigne();
  }
  printw("Score: %ld \n",grid_score(g));
  refresh();//on actualise l'affichage de la fenetre

}

