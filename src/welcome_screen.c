#include <write.h>

void	store_drawn_space_init(t_app* app, t_rect_link* rect)
{
	link_track_init(&(app->drawn_areas), (t_link*)rect);
}

t_rect_link*	create_rect_link(SDL_Rect* rect)
{
	t_rect_link* new;

	new = malloc(sizeof(t_rect_link));
	new->rect = rect;
	return (new);
}

void    set_welcome_screen(t_app* app)
{
    SDL_Surface*            logo_surface;
	SDL_Texture*			logo_texture;
    SDL_Rect*				space;
	t_rect_link*			drawn_link;

    //load logo_surface
    logo_surface = SDL_LoadBMP("ressources/logo.bmp");
	//We use a texture to display it.
	logo_texture = SDL_CreateTextureFromSurface(app->sdl_material.renderer, logo_surface);
    //Find its draw point on the canvas.
    space = malloc(sizeof(SDL_Rect));
	space->w = logo_surface->w;
	space->h = logo_surface->h;
	space->x = (app->main_window.w - space->w) / 2;
	space->y = (app->main_window.h - space->h) / 2;
    //Put its info inside drawn (but not clickable)
	drawn_link = create_rect_link(space);
	store_drawn_space_init(app, drawn_link);
    //draw it.
	if (SDL_RenderCopy(app->sdl_material.renderer, logo_texture, NULL, space))
		putendl(SDL_GetError());
    //render.
	refresh_display(app);
	link_track_remove_link(&(app->drawn_areas), (t_link*)drawn_link);
}