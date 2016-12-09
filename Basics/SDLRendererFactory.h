#pragma once
#include <SDL2/SDL.h>

class SDLRendererFactory
{
public:
	SDLRendererFactory();
	~SDLRendererFactory();

	static SDL_Renderer* Create(SDL_Window* sdlWindow);
};

