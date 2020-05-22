#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct _state_t {
	void (*init)(struct _state_t * s, SDL_Renderer *renderer);
	void (*update)(struct _state_t * s, Uint32 elapsedTime);
	void (*handleEvent)(struct _state_t * s, SDL_Renderer *renderer);
	void (*draw)(struct _state_t * s, SDL_Renderer *renderer);
	void (*clean)(struct _state_t * s);
	void * data;
} state_t;

void GS_Init();
void GS_Clean();

void GS_handleEvent(SDL_Renderer *renderer);
void GS_update();
void GS_draw(SDL_Renderer * render);

void GS_PushState(state_t * state, SDL_Renderer *renderer);
void GS_PopState();

int GS_isEmpty();

#endif
