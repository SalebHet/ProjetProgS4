#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "afficher.h"

static char* itoa(int i){
  char* ret=malloc(7*sizeof(char));
  char* copie=ret;
  memset(ret,' ',6);
  while(i!=0){
    *copie=(i%10)+48;
    copie++;
    i/=10;
  }
  ret[6]='\0';
  return ret;
}


void afficherLigne(){
    printf("_____________________________\n");
}
void afficher(grid g){
  afficherLigne();
  char *nb;
  int val;
  for(int i=0;i<GRID_SIDE;i++){
    for(int j=0;j<GRID_SIDE;j++){//la taille maxi d'un nombre est de 6,6*4+4+2=29
      val=get_tile(g,i,j);
      if(val!=0)
	val=pow(2,val);
      nb=itoa(val);
      printf("|%s",nb);
      free(nb);
    }
    printf("|\n");
    afficherLigne();
  }
  afficherLigne();
}

