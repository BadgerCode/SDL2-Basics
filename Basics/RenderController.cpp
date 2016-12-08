#include "RenderController.h"
#include <SDL2/SDL_image.h>


RenderController::RenderController(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
	_sdlRenderer = renderer;

	SDL_RenderSetLogicalSize(_sdlRenderer, screenWidth, screenHeight);
}


RenderController::~RenderController()
{
}

void RenderController::ClearScreen() const
{
	SDL_SetRenderDrawColor(_sdlRenderer, 50, 120, 255, 255);
	SDL_RenderClear(_sdlRenderer);
}

void RenderController::UpdateScreen() const
{
	SDL_RenderPresent(_sdlRenderer);
}

SDL_Texture* RenderController::LoadTexture(const std::string& str) const
{
	auto texture = IMG_LoadTexture(_sdlRenderer, str.c_str());
	//TODO: What if texture fails to load?
	if(texture == nullptr)
	{
		printf("Error loading texture");
	}
	return texture;
}

void RenderController::RenderTexture(SDL_Texture* texture, int x, int y) const
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	SDL_RenderCopy(_sdlRenderer, texture, nullptr, &rect);
}

void RenderController::DrawRectangle(SDL_Rect* rect, int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(_sdlRenderer, r, g, b, a);
	SDL_RenderFillRect(_sdlRenderer, rect);
}

void RenderController::DrawRectangleOutline(SDL_Rect* rect, int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(_sdlRenderer, r, g, b, a);
	SDL_RenderDrawRect(_sdlRenderer, rect);
}
