#include "write.h"
#include <string.h>

void		get_window_size(t_master* m, int* w, int* h)
{
	SDL_GetRendererOutputSize(m->rend, w, h);
}

t_text_edit_space* create_text_edit_space(t_master* m, const char* file_name)
{
	m->txt_edit_space = malloc(sizeof(t_text_edit_space));
	if (m->txt_edit_space == NULL)exit(0);
	if (file_name);
	else
	{
		m->txt_edit_space->text = malloc(sizeof(char));
		if (m->txt_edit_space->text == NULL)
			exit(0);
	}
	m->txt_edit_space->cursor.pos = 0;
	m->txt_edit_space->frame.x = m->win_space.w / 6;
	m->txt_edit_space->frame.w = m->win_space.w - (m->txt_edit_space->frame.x * 2);
	m->txt_edit_space->frame.y = m->win_space.h / 95;
	m->txt_edit_space->frame.h = m->win_space.h - (m->txt_edit_space->frame.y * 2);
	draw_full_rectangle(m->rend, &(m->txt_edit_space->frame), m->ligther_background);
	place_cursor(m->txt_edit_space, m->main_font);
	draw_cursor(m);
	SDL_RenderPresent(m->rend);
	return(m->txt_edit_space);
}

void		place_cursor(t_text_edit_space* edit_frame, TTF_Font *font)
{
	//The actual writing space must be a bit smaller than the visual frame.
	edit_frame->cursor.frame.x = edit_frame->frame.x + edit_frame->frame.w / 85;
	edit_frame->cursor.frame.y = edit_frame->frame.y + edit_frame->cursor.frame.x - edit_frame->frame.x;
	//dessiner un rectange d'une surface pouvant contenir le plus grand caractere du set.
	edit_frame->cursor.frame.w = CURSOR_THICKNESS;
	edit_frame->cursor.frame.h = TTF_FontHeight(font);
}

void clear_cursor(t_master* m)
{
	draw_full_rectangle(m->rend, &(m->txt_edit_space->cursor.frame), m->ligther_background);
}

void draw_cursor(t_master* m)
{
	draw_full_rectangle(m->rend, &(m->txt_edit_space->cursor.frame), m->forground);
}

void print_letter(t_master* m, char* letter)
{
	SDL_Surface*		text_surface;
	SDL_Texture*		text_texture;
	SDL_Rect			target_surface;

	text_surface = TTF_RenderText_Blended(m->main_font, letter, m->forground);
	text_texture = SDL_CreateTextureFromSurface(m->rend, text_surface);
	target_surface.x = m->txt_edit_space->cursor.frame.x;
	target_surface.y = m->txt_edit_space->cursor.frame.y;
	SDL_QueryTexture(text_texture, NULL, NULL, &(target_surface.w), &(target_surface.h));
	SDL_RenderCopy(m->rend, text_texture, NULL, &target_surface);
	m->txt_edit_space->cursor.frame.x += target_surface.w;
}

void remove_previous_letter(m)
{
	SDL_Rect* letter_surface;

	//find the size of the last letter.
	
	//remove the cursor
	clear_cursor(m);
	//replace the letter with blank. Place the cursor at the top right.
	//draw the cursor
	draw_cursor(m);
}

void edit_space_add_letter(t_master* m, char *text)
{
	strcat(m->txt_edit_space->text, text);
	clear_cursor(m);
	print_letter(m, text);
	draw_cursor(m);
	SDL_RenderPresent(m->rend);
}

void edit_space_remove_letter(t_master *m)
{
	remove_previous_letter(m);
	str_shorten(m->txt_edit_space->text, 1);
}
