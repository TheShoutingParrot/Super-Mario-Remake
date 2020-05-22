#include "GameState.h"

typedef struct _GS_Stack {
	struct _GS_Stack * prev;
	state_t * state;
} GS_Stack;

static GS_Stack * head;

void GS_Init()
{
	head = NULL;
}

void GS_Clean()
{
	while(!GS_isEmpty())
	{
		GS_PopState();
	}
}

void GS_PushState(state_t * state, SDL_Renderer *renderer)
{
	GS_Stack * newStack = malloc(sizeof(*newStack));
	newStack->state = state;
	newStack->prev = head;
	
	head = newStack;
	
	state->init(state, renderer);
}

void GS_PopState()
{
	GS_Stack * tmp = NULL;
	if(head->prev != NULL)
		tmp = head;
	
	head = head->prev;
	if(tmp != NULL)
	{
		tmp->state->clean(tmp->state);
		free(tmp->state);
		free(tmp);
	}
}

void GS_handleEvent(SDL_Renderer *renderer)
{
	head->state->handleEvent(head->state, renderer);
}

void GS_update(Uint32 elapsedTime)
{
	head->state->update(head->state, elapsedTime);
}

void GS_draw(SDL_Renderer *renderer)
{
	head->state->draw(head->state, renderer);
}

int GS_isEmpty()
{
	return head == NULL;
}
