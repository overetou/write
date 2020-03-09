#ifndef WRITE_H
#define WRITE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <libft.h>
#include <SDL2/SDL_ttf.h>

# define FONT_PATH "./raleway/Raleway-Regular.ttf"
# define FONT_SIZE 18

# define BACKGROUND 50, 50, 50, 255
# define FORGROUND 250, 250, 250, 255
# define LIGHT_BACKGROUND 65, 65, 65, 255

typedef struct  s_sdl_material
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;
}               t_sdl_material;

typedef struct  s_app
{
    TTF_Font*       main_font;
    t_sdl_material  sdl_material;
    SDL_Rect        main_window;
    SDL_Color	    background;
	SDL_Color	    ligther_background;
    SDL_Color	    forground;
}               t_app;

void	set_color(SDL_Color* color, int r, int g, int b, int a);
void    set_window_and_run(SDL_Window* window);
void    draw_and_run(t_app* app);
void    interact_with_user(t_app* app);

#endif /* WRITE_H */