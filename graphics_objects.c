#include "write.h"

void		get_window_size(t_master* m, int* w, int* h)
{
	SDL_GetRendererOutputSize(m->rend, w, h);
}

t_text_edit_space* create_text_edit_space(t_master* m, const char* file_name)
{
	t_text_edit_space* new;

	new = malloc(sizeof(t_text_edit_space));
	if (new == NULL)exit(0);
	if (file_name);
	else
	{
		new->text = malloc(sizeof(char));
		if (new->text == NULL)
			exit(0);
	}
	new->cursor.pos = 0;
	set_draw_color(m->ligther_background, m->rend);
	new->frame.x = m->win_space.w / 6;
	new->frame.w = m->win_space.w - (new->frame.x * 2);
	new->frame.y = m->win_space.h / 95;
	new->frame.h = m->win_space.h - (new->frame.y * 2);
	SDL_RenderFillRect(m->rend, &(new->frame));
	place_cursor(new, m->main_font);
	set_draw_color(m->forground, m->rend);
	SDL_RenderFillRect(m->rend, &(new->cursor.frame));
	SDL_RenderPresent(m->rend);
	return(new);
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
