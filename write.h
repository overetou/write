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

typedef struct s_line_meta
{
	t_link* next;
	int	endline_x;
}t_line_meta;

typedef struct	s_cursor
{
	size_t		pos;
	SDL_Texture* img_save;
	SDL_Rect		frame;
}				t_cursor;

typedef struct s_abs_rect
{
	int	x;
	int	y;
	int	right_x;
	int	right_y;
}				t_abs_rect;

typedef struct	s_text_edit_space
{
	t_cursor		cursor;
	SDL_Rect		frame;
	t_abs_rect inner_frame;
	t_track lines_meta;
	char* text;
	FILE* linked_file;
}				t_text_edit_space;

typedef struct	s_master
{
	SDL_Window* win;
	t_space		win_space;
	SDL_Renderer* rend;
	TTF_Font* main_font;
	t_text_edit_space* txt_edit_space;
	SDL_Color	background;
	SDL_Color	ligther_background;
	SDL_Color	forground;
}				t_master;

void		get_window_size(t_master* m, int* w, int* h);
t_text_edit_space* create_text_edit_space(t_master* m, const char* file_name);
void		place_cursor(t_text_edit_space* edit_frame, TTF_Font *font);
void		clear_cursor(t_master* m);
void		draw_cursor(t_master *m);
void		print_letter(t_master* m, char *letter);
void		remove_previous_letter(t_master *m);
void		edit_space_add_letter(t_master* m, char *text);
void		edit_space_remove_letter(t_master *m);
t_line_meta* line_meta_init(int x);
#endif