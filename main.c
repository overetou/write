#include "write.h"

void		event_loop(t_master* m)
{
	SDL_Event	event;
	SDL_bool		fine = SDL_TRUE;

	while (fine)
	{
		SDL_WaitEvent(&event);
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			fine = SDL_FALSE;
		}
	}
	(void)m;
}

void		app_exec(t_master* m)
{
	SDL_Surface*		text_surface;
	SDL_Texture*		text_texture;
	SDL_Rect			target_surface;

	set_background(m->rend, m->background);
	//text_surface = TTF_RenderText_Blended(m->main_font, "Bonjour!", m->forground);
	//text_texture = SDL_CreateTextureFromSurface(m->rend, text_surface);
	//target_surface.x = 20; target_surface.y = 20;
	//SDL_QueryTexture(text_texture, NULL, NULL, &(target_surface.w), &(target_surface.h));
	//SDL_RenderCopy(m->rend, text_texture, NULL, &target_surface);
	//SDL_RenderPresent(m->rend);
	t_text_edit_space* edit_space = create_text_edit_space(m, NULL);
	event_loop(m);
	free(edit_space->text);
	free(edit_space);
}

void		init_graphics(t_master* m)
{
	sdl_test_success(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL init failed.");
	m->win = SDL_CreateWindow("Write", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	sdl_test_success(m->win != NULL, "Window creation failed.");
	m->rend = SDL_CreateRenderer(m->win, -1, 0);
	sdl_test_success(m->rend != NULL, "Renderer creation failed.");

	sdl_test_success(TTF_Init() >= 0, "Font library init failed.");
	m->main_font = TTF_OpenFont("raleway/Raleway-Regular.ttf", 18);
	sdl_test_success(m->main_font != NULL, TTF_GetError());
	set_color(&(m->background), BACKGROUND);
	set_color(&(m->forground), FORGROUND);
	set_color(&(m->ligther_background), LIGHT_BACKGROUND);

	get_window_size(m, &(m->win_space.w), &(m->win_space.h));
}

void		app_quit(t_master* m)
{
	TTF_CloseFont(m->main_font);
	sdl_quit();
}

int	main(void)
{
	t_master		m;

	init_graphics(&m);
	app_exec(&m);
	app_quit(&m);
	return (0);
}