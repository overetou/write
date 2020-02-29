#include "write.h"
#include "libft.h"

void		get_window_size(t_master* m, int* w, int* h)
{
	SDL_GetRendererOutputSize(m->rend, w, h);
}

void print_letter(t_master* m, char* letter)
{
	SDL_Surface*		text_surface;
	SDL_Texture*		text_texture;
	SDL_Rect			target_surface;

	//create the text texture.
	text_surface = TTF_RenderText_Blended(m->main_font, letter, m->forground);
	text_texture = SDL_CreateTextureFromSurface(m->rend, text_surface);
	//place the texture
	SDL_QueryTexture(text_texture, NULL, NULL, &(target_surface.w), &(target_surface.h));
	if (m->txt_edit_space->cursor.frame.x + target_surface.w + CURSOR_THICKNESS > m->txt_edit_space->inner_frame.right_x)
	{
		track_add(&(m->txt_edit_space->lines_meta), (t_link*)line_meta_init(m->txt_edit_space->cursor.frame.x));
		m->txt_edit_space->cursor.frame.x = m->txt_edit_space->inner_frame.x;
		m->txt_edit_space->cursor.frame.y += TTF_FontLineSkip(m->main_font);
	}
	rect_copy_coord(&(m->txt_edit_space->cursor.frame), &target_surface);
	SDL_RenderCopy(m->rend, text_texture, NULL, &target_surface);
	//update the cursor position
	m->txt_edit_space->cursor.frame.x += target_surface.w;
	(m->txt_edit_space->cursor.pos)++;
}

void		get_letter_size(char* txt, TTF_Font* font, SDL_Rect* frame)
{
	char		isolate[2];

	isolate[0] = txt[0];
	isolate[1] = '\0';
	TTF_SizeText(font, isolate, &(frame->w), &(frame->h));
}

void remove_previous_letter(t_master *m)
{
	SDL_Rect letter_frame;

	//find the size of the last letter.
	
	//remove the cursor
	clear_cursor(m);
	//replace the letter with blank. Place the cursor at the top right.
	get_letter_size(m->txt_edit_space->text + m->txt_edit_space->cursor.pos, m->main_font, &letter_frame);
	letter_frame.x = m->txt_edit_space->cursor.frame.x - letter_frame.w;
	letter_frame.y = m->txt_edit_space->cursor.frame.y;
	draw_full_rectangle(m->rend, &letter_frame, m->ligther_background);
	//push cursor back.
	if (letter_frame.x == m->txt_edit_space->inner_frame.x &&
		letter_frame.y != m->txt_edit_space->inner_frame.y)
	{
		m->txt_edit_space->cursor.frame.x = get_last_l_meta(m->txt_edit_space)->endline_x;
		track_remove_last(&(m->txt_edit_space->lines_meta), free);
		m->txt_edit_space->cursor.frame.y -= TTF_FontLineSkip(m->main_font);
	}
	else
		rect_copy_coord(&letter_frame, &(m->txt_edit_space->cursor.frame));
	//draw the cursor
	draw_cursor(m);
}

void edit_space_add_letter(t_master* m, char *text)
{
	m->txt_edit_space->text = str_add(m->txt_edit_space->text, text, 1);
	clear_cursor(m);
	print_letter(m, text);
	draw_cursor(m);
	SDL_RenderPresent(m->rend);
}

void edit_space_remove_letter(t_master *m)
{
	if (m->txt_edit_space->cursor.pos == 0)
		return;
	(m->txt_edit_space->cursor.pos)--;
	remove_previous_letter(m);
	SDL_RenderPresent(m->rend);
	m->txt_edit_space->text = str_shorten(m->txt_edit_space->text, 1);
}