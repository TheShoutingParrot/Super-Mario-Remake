#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct _state_t {
	void (*init)(struct _state_t * s);
	void (*update)(struct _state_t * s, uint32_t elapsedTime);
	void (*handleEvent)(struct _state_t * s);
	void (*draw)(struct _state_t * s);
	void (*clean)(struct _state_t * s);
	void * data;
} state_t;

void GS_Init(void);
void GS_Clean(void);

void GS_handleEvent(void);
void GS_update(uint32_t elapsedTime);
void GS_draw(void);

void GS_PushState(state_t * state);
void GS_PopState(void);

int GS_isEmpty(void);

#endif
