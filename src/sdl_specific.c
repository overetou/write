#include <write.h>

void	store_window_size(SDL_Renderer* renderer, SDL_Rect* frame)
{
	SDL_GetRendererOutputSize(renderer, &(frame->w), &(frame->h));
}

void    set_sdl_material(t_sdl_material* to_fill, SDL_Window* win, SDL_Renderer* rend)
{
    to_fill->window = win;
    to_fill->renderer = rend;
}

void    finish_setup_and_run(SDL_Window* window, SDL_Renderer* renderer)
{
    t_app       app;

    app.main_font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (app.main_font)
    {
        set_color(&(app.background), BACKGROUND);
	    set_color(&(app.forground), FORGROUND);
        set_color(&(app.ligther_background), LIGHT_BACKGROUND);
        store_window_size(renderer, &(app.main_window));
        set_sdl_material(&(app.sdl_material), window, renderer);
        draw_and_run(&app);
        TTF_CloseFont(app.main_font);
    }
    else
        putendl(TTF_GetError());
}

void    set_window_and_run(SDL_Window* window)
{
    SDL_Renderer*   renderer;

    renderer = SDL_CreateRenderer(window, -1,
    SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (renderer)
    {
        if (TTF_Init() == 0)
        {
            finish_setup_and_run(window, renderer);
            TTF_Quit();
        }
        else
            putendl(TTF_GetError());
        SDL_DestroyRenderer(renderer);
    }
    else
        putendl(SDL_GetError());
}