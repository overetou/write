#pragma once
#ifndef WRITE_H
#define WRITE_H
#define BACKGROUND 50, 50, 50, 255
#define FORGROUND 245, 245, 245, 255
#define LIGHT_BACKGROUND 65, 65, 65, 255
#define W_PARAMS "Write", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN
#define CURSOR_THICKNESS 3

#include "libgraphic.h"
#include <SDL.h>
#include <stdio.h>

typedef struct	s_cursor
{
	size_t		pos;
	SDL_Texture* img_save;
	SDL_Rect		frame;
}				t_cursor;

typedef struct	s_text_edit_space
{
	t_cursor		cursor;
	SDL_Rect		frame;
	char* text;
	FILE* linked_file;
}				t_text_edit_space;

typedef struct	s_master
{
	SDL_Window* win;
	t_space		win_space;
	SDL_Renderer* rend;
	TTF_Font* main_font;
	SDL_Color	background;
	SDL_Color	ligther_background;
	SDL_Color	forground;
}				t_master;

void		get_window_size(t_master* m, int* w, int* h);
t_text_edit_space* create_text_edit_space(t_master* m, const char* file_name);
void		place_cursor(t_text_edit_space* edit_frame, TTF_Font *font);
#endif