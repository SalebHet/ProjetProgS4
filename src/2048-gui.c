

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <assert.h>

#include "grid.h"

typedef enum {MOVE_UP=UP,MOVE_LEFT=LEFT,MOVE_DOWN=DOWN,MOVE_RIGHT=RIGHT,RUN,QUIT} state;
typedef struct{
  state st;
  grid g;
} *game;
game new_game(){
  game g=malloc(sizeof(game*));
  g->st=RUN;
  g->g=new_grid();
  return g;
}


typedef struct{
  SDL_Surface* screen;
  TTF_Font* font;
} *vars_draw;
vars_draw new_vars_draw(){
  vars_draw v=malloc(sizeof(vars_draw));
  v->screen=SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE );
  v->font=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",24);
  return v;
}


void event(game g){
  SDL_Event* event=malloc(sizeof(SDL_Event));
  while(SDL_PollEvent(event)){
    if(event->type==SDL_KEYDOWN){
      if(event->key.keysym.sym==SDLK_ESCAPE){
	g->st=QUIT;
      }
    }
  }
}

void draw(vars_draw v,game g){

}

void execute(game g){
  if(g->st<RUN){
    dir d=g->st;
    if(can_move(g->g,d))
      play(g->g,d);
    g->st=RUN;
  }
}
int main(int argc,char** argv){
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  game g=new_game();
  vars_draw v=new_vars_draw();
  while(g->st!=QUIT){
    event(g);
    execute(g);
    draw(v,g);
  }
  SDL_Quit();
  return EXIT_SUCCESS;
}
