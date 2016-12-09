#include "SDLWindowFactory.h"



SDLWindowFactory::SDLWindowFactory()
{
}


SDLWindowFactory::~SDLWindowFactory()
{
}

SDL_Window* SDLWindowFactory::Create(const char* windowTitle, int screenWidth, int screenHeight)
{
	return SDL_CreateWindow(windowTitle,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_OPENGL);
}
