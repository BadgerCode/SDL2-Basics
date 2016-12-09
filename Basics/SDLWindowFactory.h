#pragma once
#include <SDL2/SDL.h>

class SDLWindowFactory
{
public:
	SDLWindowFactory();
	~SDLWindowFactory();

	static SDL_Window* Create(const char* windowTitle, int screenWidth, int screenHeight);
};

