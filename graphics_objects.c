#include "write.h"

void		get_window_size(t_master* m, int* w, int* h)
{
	SDL_GetRendererOutputSize(m->rend, w, h);
}

char		*one_byte_string(void)
{
	char* new;

	new = malloc(sizeof(char));
	sdl_test_success(new != NULL, "One byte malloc failed.");
	new[0] = '\0';
	return (new);
}

void		set_t_e_inner_frame(t_text_edit_space* edit_frame)
{
	int	margin_size;

	//The actual writing space must be a bit smaller than the visual frame.
	margin_size = edit_frame->frame.w / 85;
	edit_frame->inner_frame.x = edit_frame->frame.x + margin_size;
	edit_frame->inner_frame.y = edit_frame->frame.y + margin_size;
	edit_frame->inner_frame.right_x = edit_frame->frame.x + edit_frame->frame.w - margin_size;
	edit_frame->inner_frame.right_y = edit_frame->frame.y + edit_frame->frame.h - margin_size;
}

t_text_edit_space* create_text_edit_space(t_master* m, const char* file_name)
{
	m->txt_edit_space = malloc(sizeof(t_text_edit_space));
	if (m->txt_edit_space == NULL)exit(0);
	if (file_name);
	else
	{
		m->txt_edit_space->text = one_byte_string();
		if (m->txt_edit_space->text == NULL)
			exit(0);
	}
	m->txt_edit_space->cursor.pos = 0;
	m->txt_edit_space->frame.x = m->win_space.w / 6;
	m->txt_edit_space->frame.w = m->win_space.w - (m->txt_edit_space->frame.x * 2);
	m->txt_edit_space->frame.y = m->win_space.h / 95;
	m->txt_edit_space->frame.h = m->win_space.h - (m->txt_edit_space->frame.y * 2);
	draw_full_rectangle(m->rend, &(m->txt_edit_space->frame), m->ligther_background);
	set_t_e_inner_frame(m->txt_edit_space);
	place_cursor(m->txt_edit_space, m->main_font);
	draw_cursor(m);
	SDL_RenderPresent(m->rend);
	return(m->txt_edit_space);
}

void		place_cursor(t_text_edit_space* edit_frame, TTF_Font* font)
{
	edit_frame->cursor.pos = 0;
	edit_frame->cursor.frame.x = edit_frame->inner_frame.x;
	edit_frame->cursor.frame.y = edit_frame->inner_frame.y;
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

	//create the text texture.
	text_surface = TTF_RenderText_Blended(m->main_font, letter, m->forground);
	text_texture = SDL_CreateTextureFromSurface(m->rend, text_surface);
	//place the texture
	SDL_QueryTexture(text_texture, NULL, NULL, &(target_surface.w), &(target_surface.h));
	if (m->txt_edit_space->cursor.frame.x + target_surface.w + CURSOR_THICKNESS > m->txt_edit_space->inner_frame.right_x)
	{
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
		m->txt_edit_space->cursor.frame.x = m->txt_edit_space->inner_frame.right_x - CURSOR_THICKNESS;
		m->txt_edit_space->cursor.frame.y -= TTF_FontLineSkip(m->main_font);
	}
	else
		rect_copy_coord(&letter_frame, &(m->txt_edit_space->cursor.frame));
	//draw the cursor
	draw_cursor(m);
}

void		strcopy(char* dest, char* source)
{
	while (*source)
	{
		*dest = *source;
		source++;
		dest++;
	}
	*dest = '\0';
}

char		*str_add(char* str, char* add, size_t add_len)
{
	size_t	base_len;

	base_len = strlen(str);
	str = realloc(str, base_len + add_len + 1);
	sdl_test_success(str != NULL, "str_add malloc failed.");
	strcopy(str + base_len, add);
	return (str);
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
