#pragma once

#include "SDL2/SDL.h"

class RenderController
{
public:
	RenderController(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	~RenderController();

	void ClearScreen() const;
	void DrawPlayer(int playerX, int playerY) const;
	void UpdateScreen() const;

private :
	SDL_Renderer* _sdlRenderer;
};

