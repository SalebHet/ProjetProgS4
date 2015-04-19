

#include <SDL/SDL.h>
#include <stdlib.h>

#include "grid.h"

typedef enum {MOVE_UP,MOVE_LEFT,MOVE_DOWN,MOVE_RIGHT,RUN,QUIT} state;
typedef struct{
  state st;
  grid g;
} game;

void event(game* g){
  SDL_Event* event=malloc(sizeof(SDL_Event));
  while(SDL_PollEvent(event)){
    if(event->type==SDL_KEYDOWN){
      if(event->key.keysym.sym==SDLK_ESCAPE){
	g->st=QUIT;
      }
    }
  }
}

void draw(SDL_Surface* screen,game* g){

}

void execute(game* g){

}
int main(int argc,char** argv){
  SDL_Init(SDL_INIT_VIDEO);
  game* g=malloc(sizeof(game));
  g->st=RUN;
  SDL_Surface* screen=SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE );
  while(g->st!=QUIT){
    event(g);
    execute(g);
    draw(screen,g);
  }
  SDL_Quit();
  return EXIT_SUCCESS;
}
