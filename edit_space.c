#include "write.h"

t_text_edit_space* create_text_edit_space(t_master* m, const char* file_name)
{
	m->txt_edit_space = malloc(sizeof(t_text_edit_space));
	if (m->txt_edit_space == NULL)exit(0);
	if (file_name)
	{
		m->txt_edit_space->linked_file = SDL_RWFromFile(file_name, "rw");
		if (m->txt_edit_space->linked_file == NULL)
			exit(0);
		Sint64 file_size = SDL_RWsize(m->txt_edit_space->linked_file);
		m->txt_edit_space->text = malloc(file_size);
		if (SDL_RWread(m->txt_edit_space->linked_file, m->txt_edit_space->text, file_size, 1) == 0)
			exit(0);
	}
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
	//init the line meta track. This link will never be used but will allow us to just add future links.
	track_init(&(m->txt_edit_space->lines_meta), (t_link*)line_meta_init(0));

	return(m->txt_edit_space);
}

t_line_meta* get_last_l_meta(t_text_edit_space* edit_space)
{
	return ((t_line_meta*)(edit_space->lines_meta.last));
}

void		set_t_e_inner_frame(t_text_edit_space* edit_frame)
{
	int	margin_size;

	//The actual writing space (inner_frame here) must be a bit smaller than the visual frame.
	margin_size = edit_frame->frame.w / 85;
	edit_frame->inner_frame.x = edit_frame->frame.x + margin_size;
	edit_frame->inner_frame.y = edit_frame->frame.y + margin_size;
	edit_frame->inner_frame.right_x = edit_frame->frame.x + edit_frame->frame.w - margin_size;
	edit_frame->inner_frame.right_y = edit_frame->frame.y + edit_frame->frame.h - margin_size;
}

void clear_cursor(t_master* m)
{
	draw_full_rectangle(m->rend, &(m->txt_edit_space->cursor.frame), m->ligther_background);
}

void draw_cursor(t_master* m)
{
	draw_full_rectangle(m->rend, &(m->txt_edit_space->cursor.frame), m->forground);
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

t_line_meta* line_meta_init(int x)
{
	t_line_meta* new;

	new = malloc(sizeof(t_line_meta));
	sdl_test_success(new != NULL, "Failed to allocate a line meta link.");
	new->endline_x = x;
	return (new);
}

void		edit_space_save(t_master* m) {
	(void)m;
}