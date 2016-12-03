#pragma once

#include "SDL2/SDL.h"

class RenderController
{
public:
	RenderController(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	~RenderController();

	void ClearScreen() const;
	void UpdateScreen() const;

	void DrawRectangle(SDL_Rect* rect, int r, int g, int b, int a) const;
	void DrawRectangleOutline(SDL_Rect* rect, int r, int g, int b, int a) const;

private :
	SDL_Renderer* _sdlRenderer;
};

