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

void    draw_and_run(t_app* app)
{
    if (set_background(app->sdl_material.renderer, app->background))
    {
        set_welcome_screen(app);
        interact_with_user(app);
    }
    else
        putendl("Failed to set background");
}