#include "SDLRendererFactory.h"



SDLRendererFactory::SDLRendererFactory()
{
}


SDLRendererFactory::~SDLRendererFactory()
{
}

SDL_Renderer* SDLRendererFactory::Create(SDL_Window* sdlWindow)
{
	return SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
}
