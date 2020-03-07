#include <write.h>

void		set_color(SDL_Color* color, int r, int g, int b, int a)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
}

BOOL		set_draw_color(SDL_Color color, SDL_Renderer* r)
{
	int	return_val;

	return_val = SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
	if (return_val == 0)
        return 1;
    return 0;
}

BOOL	set_background(SDL_Renderer* r, SDL_Color bg)
{
	if (set_draw_color(bg, r))
    {
    	if (SDL_RenderClear(r) == 0)
        {
	        SDL_RenderPresent(r);
            return 1;
        }
        else
            putendl(SDL_GetError());
    }
    else
        putendl("set_draw_color failed.");
    return 0;
}

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
        interact_with_user(app);
    else
        putendl("Failed to set background");
}