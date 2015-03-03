#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "afficher.h"

static char* itoa(int i){
  char* ret=malloc(7*sizeof(char));
  char* copie=ret+5;
  memset(ret,' ',6);
  while(i!=0){
    *copie=(i%10)+48;
    copie--;
    i/=10;
  }
  ret[6]='\0';
  return ret;
}


void afficherLigne(){
  printf("+");
  for(int i=0;i<GRID_SIDE;i++)
    printf("------+");
  printf("\n");
}
void afficher(grid g){
  afficherLigne();
  char *nb;
  int val;
  for(int j=0;j<GRID_SIDE;j++){
    for(int i=0;i<GRID_SIDE;i++){
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
}

