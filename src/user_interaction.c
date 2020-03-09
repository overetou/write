#include <write.h>

void    interact_with_user(t_app* app)
{
    SDL_Event	event;
	SDL_bool	keep_going = SDL_TRUE;

    (void)app;
	while (keep_going)
	{
		SDL_WaitEvent(&event);
		if (event.key.keysym.sym == SDLK_ESCAPE)
            keep_going = SDL_FALSE;
	}
}