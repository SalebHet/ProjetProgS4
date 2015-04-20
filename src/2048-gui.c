

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

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
  add_tile(g->g);
  add_tile(g->g);
  return g;
}


typedef struct{
  SDL_Surface* screen;
  TTF_Font** fonts;
} *vars_draw;
vars_draw new_vars_draw(){
  vars_draw v=malloc(sizeof(vars_draw));
  v->screen=SDL_SetVideoMode( 400,400, 16, SDL_HWSURFACE );
  v->fonts=malloc(sizeof(TTF_Font*)*2);
  v->fonts[0]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",60);
  v->fonts[1]=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf",40);
  return v;
}


void event(game g){
  SDL_Event* event=malloc(sizeof(SDL_Event));
  while(SDL_PollEvent(event)){
    switch(event->type){
    case SDL_KEYDOWN:
      switch(event->key.keysym.sym){
      case SDLK_ESCAPE:
	g->st=QUIT;
	break;
      case SDLK_UP:
	g->st=MOVE_UP;
	break;
      case SDLK_DOWN:
	g->st=MOVE_DOWN;
	break;
      case SDLK_RIGHT:
	g->st=MOVE_RIGHT;
	break;
      case SDLK_LEFT:
	g->st=MOVE_LEFT;
	break;
      default:
	break;
      }
      break;
    case SDL_QUIT:
      g->st=QUIT;
      break;
    default:
      break;
    }
  }
}

void draw(vars_draw v,game g){
  Uint32 rmask, gmask, bmask, amask;

 rmask = 0xff000000;
 gmask = 0x00ff0000;
 bmask = 0x0000ff00;
 amask = 0x000000ff;

 SDL_Surface *tile=SDL_CreateRGBSurface(SDL_HWSURFACE,100,100,32,rmask,gmask,bmask,amask);

 SDL_FillRect(tile, NULL,SDL_MapRGBA(tile->format,0,0,0,0));
 SDL_Rect rect={5,5,90,90};
  SDL_Color c={255,255,255};
  char* str=malloc(10*sizeof(char));
  SDL_FillRect(tile, &rect,SDL_MapRGB(tile->format,80,80,80)); 
  SDL_FillRect(v->screen, NULL, SDL_MapRGB(v->screen->format, 100, 100, 100));
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      int t=get_tile(g->g,x,y);
      SDL_Rect tilePos={100*x,100*y};
      SDL_BlitSurface(tile,NULL,v->screen,&tilePos);
      if(t==0)
	continue;
      t=pow(2,t);
      int taille=sprintf(str,"%d",t);
      SDL_Surface* s=TTF_RenderText_Solid( v->fonts[taille<3?0:1], str, c );
      

      SDL_BlitSurface(s,NULL,v->screen,&tilePos);
    }
  }

  SDL_Flip(v->screen);
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
