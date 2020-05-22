#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameState.h"
#include "MainState.h"
#include "config.h"

int main(int argc, char *args[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	Uint32 lastUpdate = 0, currentTime = 0, elapsedTime = 0;
	
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Super Mario Bros", 
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_W, SCREEN_H,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, SCREEN_W, SCREEN_H);

	GS_Init();
	
	GS_PushState(MS_get(), renderer);
	
	GS_handleEvent(renderer);
	while(!GS_isEmpty())
	{
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - lastUpdate;
		if(elapsedTime >= REFRESH_TIME)
		{
			GS_update(elapsedTime);
			lastUpdate = currentTime;
		}
	
		SDL_RenderClear(renderer);	
		GS_draw(renderer);
		SDL_RenderPresent(renderer);
		
		GS_handleEvent(renderer);
	}
	
	GS_Clean();
	
	SDL_Quit();
	IMG_Quit();

	return 0;
}
