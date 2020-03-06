#pragma once
#ifndef LIBGRAPHIC_H
# define LIBGRAPHIC_H

//#include "~/Darkvale_Technologies/config/libft/header/libft.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

typedef struct s_space
{
	int w;
	int h;
}				t_space;

void	exit_msg(const char* str);
void	sdl_quit(void);
void	sdl_msg_quit(const char* s);
void	sdl_test_success(char test, const char* str);
void	set_background(SDL_Renderer* r, SDL_Color bg);
void	set_color(SDL_Color* color, int r, int g, int b, int a);
void		set_draw_color(SDL_Color color, SDL_Renderer* r);

#endif