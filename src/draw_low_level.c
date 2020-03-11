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
	        //SDL_RenderPresent(r);
            return 1;
        }
        else
            putendl(SDL_GetError());
    }
    else
        putendl(SDL_GetError());
    return 0;
}

void	refresh_display(t_app* app)
{
	SDL_RenderPresent(app->sdl_material.renderer);
}