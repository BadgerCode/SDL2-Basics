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

void RenderController::DrawPlayer(int playerX, int playerY) const
{
	SDL_Rect r;
	r.x = playerX;
	r.y = playerY;
	r.w = 25;
	r.h = 75;

	SDL_SetRenderDrawColor(_sdlRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(_sdlRenderer, &r);

	SDL_SetRenderDrawColor(_sdlRenderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(_sdlRenderer, &r);
}

void RenderController::UpdateScreen() const
{
	SDL_RenderPresent(_sdlRenderer);
}
