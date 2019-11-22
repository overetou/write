#include "libgraphic.h"

void		set_color(SDL_Color* color, int r, int g, int b, int a)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
}

void		set_draw_color(SDL_Color color, SDL_Renderer* r)
{
	int	return_val;

	return_val = SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
	if (return_val)
		sdl_msg_quit("failed to set draw color.");
}

void		set_background(SDL_Renderer* r, SDL_Color bg)
{
	set_draw_color(bg, r);
	SDL_RenderClear(r);
	SDL_RenderPresent(r);
}

void		draw_full_rectangle(SDL_Renderer* rend, SDL_Rect* rect, SDL_Color color)
{
	set_draw_color(color	, rend);
	SDL_RenderFillRect(rend, rect);
}