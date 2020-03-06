#include "libgraphic.h"
#include <stdlib.h>
#include <stdio.h>

void	exit_msg(const char* str)
{
	puts(str);
	exit(0);
}

void	sdl_quit(void)
{
	TTF_Quit();
	SDL_Quit();
}

void	sdl_msg_quit(const char* s)
{
	sdl_quit();
	exit_msg(s);
}

void	sdl_test_success(char test, const char* str)
{
	if (!test)
		sdl_msg_quit(str);
}