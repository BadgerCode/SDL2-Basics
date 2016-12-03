#include "RenderController.h"


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
