#include "main.h"
#include "GameState.h"
#include "MainState.h"
#include "config.h"

bool initGraphics(void);

int main(int argc, char *args[]) {

	Uint32 lastUpdate = 0, currentTime = 0, elapsedTime = 0;
	
	if(!initGraphics())
		return 1;

	GS_Init();
	
	GS_PushState(MS_get());
	
	GS_handleEvent();
	while(!GS_isEmpty()) {
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - lastUpdate;
		if(elapsedTime >= GAME_REFRESH_TIME)
		{
			GS_update(elapsedTime);
			lastUpdate = currentTime;
		}

		SDL_RenderClear(gRenderer);	
		GS_draw();
		SDL_RenderPresent(gRenderer);
		
		GS_handleEvent();

		if((currentTime - SDL_GetTicks()) < FPS_TIME) {
			SDL_Delay(FPS_TIME - (currentTime - SDL_GetTicks()));
		}
	}
	
	GS_Clean();
	
	SDL_Quit();
	IMG_Quit();

	return 0;
}

bool initGraphics(void) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to initialize SDL");
		return false;
	}

	gWindow = SDL_CreateWindow("Super Mario Bros", 
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_W, SCREEN_H,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if(gWindow == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to initialize window");
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	if(gRenderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to initialize renderer");
		return false;
	}

	SDL_RenderSetLogicalSize(gRenderer, SCREEN_W, SCREEN_H);

	return true;
}
