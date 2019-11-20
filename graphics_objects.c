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
	new->space.x = m->win_space.w / 6;
	new->space.w = m->win_space.w - (new->space.x * 2);
	new->space.y = m->win_space.h / 95;
	new->space.h = m->win_space.h - (new->space.y * 2);
	SDL_RenderFillRect(m->rend, &(new->space));
	SDL_RenderPresent(m->rend);
	return(new);
}