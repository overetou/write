#include "write.h"

void		event_loop(t_master* m)
{
	SDL_Event	event;
	SDL_bool		fine = SDL_TRUE;

	while (fine)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				fine = SDL_FALSE;
			else if (event.key.keysym.sym == SDLK_BACKSPACE)
				edit_space_remove_letter(m);
			else if (event.key.keysym.sym == SDLK_s && SDL_GetModState() & KMOD_CTRL)
				edit_space_save(m);
		}
		else if (event.type == SDL_TEXTINPUT)
		{
			edit_space_add_letter(m, event.text.text);
		}
	}
}

void		app_exec(t_master* m)
{
	set_background(m->rend, m->background);
	m->txt_edit_space = create_text_edit_space(m, NULL);
	event_loop(m);
}

void		init_graphics(t_master* m)
{
	//Start the sdl
	sdl_test_success(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL init failed.");
	//Start the window
	m->win = SDL_CreateWindow("Write", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	sdl_test_success(m->win != NULL, "Window creation failed.");
	//Create renderer
	m->rend = SDL_CreateRenderer(m->win, -1, 0);
	sdl_test_success(m->rend != NULL, "Renderer creation failed.");

	//Start text library for sdl
	sdl_test_success(TTF_Init() >= 0, "Font library init failed.");
	//Open font
	m->main_font = TTF_OpenFont("raleway/Raleway-Regular.ttf", 18);
	sdl_test_success(m->main_font != NULL, TTF_GetError());
	//Set background color
	set_color(&(m->background), BACKGROUND);
	//Set text color
	set_color(&(m->forground), FORGROUND);
	//Set current page color
	set_color(&(m->ligther_background), LIGHT_BACKGROUND);

	get_window_size(m, &(m->win_space.w), &(m->win_space.h));
	//Start text input
	SDL_StartTextInput();
}

void		app_quit(t_master* m)
{
	free(m->txt_edit_space->text);
	free(m->txt_edit_space);
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