#include "main.h"
#include "Mario.h"

void Mario_init(Mario * mario)
{
	SDL_Surface *loadedSurface;
	SDL_Rect * frames = NULL;
	
	loadedSurface = IMG_Load("images/mario.png");
	mario->image = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); 


	mario->currentAnimation = IDLE_SMALL_RIGHT;
	mario->direction = RIGHT;
	mario->is_moving = 0;
	mario->speed = 0.12;
	mario->currentFrame = 0;
	mario->position.x = 0;
	mario->position.y = 192;
	mario->position.w = 16;
	mario->position.h = 16;
	
	/* IDLE_SMALL_RIGHT */
	frames = malloc(sizeof(*frames));
	frames[0].x = 211;
	frames[0].y = 0;
	frames[0].w = 13;
	frames[0].h = 16;
	mario->animation[IDLE_SMALL_RIGHT].frames = frames;
	mario->animation[IDLE_SMALL_RIGHT].countFrame = 1;
	mario->animation[IDLE_SMALL_RIGHT].delay = 0;
	
	SDL_RenderCopy(gRenderer, mario->image, (mario->animation[IDLE_SMALL_RIGHT].frames), NULL);
	SDL_RenderPresent(gRenderer);
	SDL_Delay(1000);

	/* WALKING_SMALL_RIGHT */
	frames = malloc(sizeof(*frames) * 3);
	frames[0].x = 241;
	frames[0].y = 0;
	frames[0].w = 14;
	frames[0].h = 15;
	frames[1].x = 272;
	frames[1].y = 0;
	frames[1].w = 12;
	frames[1].h = 16;
	frames[2].x = 300;
	frames[2].y = 0;
	frames[2].w = 16;
	frames[2].h = 16;
	mario->animation[WALKING_SMALL_RIGHT].frames = frames;
	mario->animation[WALKING_SMALL_RIGHT].countFrame = 3;
	mario->animation[WALKING_SMALL_RIGHT].delay = 120;
}

void Mario_move_left(Mario * mario, int move)
{
	if(mario->is_moving == 1)
	{
		if(move == 0 && mario->direction == LEFT)
		{
			mario->is_moving = 0;
		}
	}
	else
	{
		if(move == 1)
		{
			mario->is_moving = 1;
			mario->direction = LEFT;
		}
	}
}

void Mario_move_right(Mario * mario, int move)
{
	if(mario->is_moving == 1)
	{
		if(move == 0 && mario->direction == RIGHT)
		{
			mario->is_moving = 0;
			mario->currentAnimation = IDLE_SMALL_RIGHT;
			mario->currentFrame = 0;
		}
	}
	else
	{
		if(move == 1)
		{
			mario->is_moving = 1;
			mario->direction = RIGHT;
			mario->currentAnimation = WALKING_SMALL_RIGHT;
		}
	}
}

void Mario_update(Mario * mario, Uint32 timeElapsed)
{
	if(mario->is_moving == 1)
	{
		mario->lastUpdate += timeElapsed;
		if(mario->lastUpdate > mario->animation[mario->currentAnimation].delay)
		{
			mario->currentFrame = (mario->currentFrame + 1) % mario->animation[mario->currentAnimation].countFrame;
			mario->lastUpdate -= mario->animation[mario->currentAnimation].delay;
		}
		
		if(mario->direction == RIGHT)
		{
			mario->position.x += (mario->speed * timeElapsed);
		}
		else
		{
			mario->position.x -= (mario->speed * timeElapsed);
			if(mario->position.x < 0)
				mario->position.x = 0;
		}
	}
}

void Mario_draw(Mario * mario, SDL_Rect offset)
{
	int cf = mario->currentFrame;
	SDL_Rect tmp_pos = mario->position;
	tmp_pos.x -= offset.x;
	tmp_pos.y -= offset.y;
	SDL_RenderCopy(gRenderer, mario->image, &(mario->animation[mario->currentAnimation].frames[cf]), &tmp_pos);

	printf("%p %d %d\n", mario->image, tmp_pos.x, tmp_pos.w);
}

void Mario_clean(Mario * mario)
{
	SDL_DestroyTexture(mario->image);
	free(mario->animation[IDLE_SMALL_RIGHT].frames);
}
