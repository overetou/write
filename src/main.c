#include <write.h>

int main()
{
    SDL_Window* window;

    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
    	//log_s("sdl inited");
        window = SDL_CreateWindow("Story Line",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_RESIZABLE);
        if (window)
        {
            //log_s("window opened");
            set_window_and_run(window);
            SDL_DestroyWindow(window);
        }
        else
            putendl(SDL_GetError());
        SDL_Quit();
    }
    else
        putendl(SDL_GetError());
    return 0;
}
