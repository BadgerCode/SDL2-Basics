#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "RenderableSDLTexture.h"
#include <vector>
#include "TextureController.h"
#include "WorldPositionController.h"

class WorldPositionController;

class RenderController
{
public:
	RenderController(SDL_Renderer* renderer, TextureController* textureController, WorldPositionController* worldPositionController, int screenWidth, int screenHeight);
	~RenderController();

	void ClearScreen() const;
	void UpdateScreen() const;

	void RenderWorldTexture(RenderableSDLTexture* texture, int x, int y) const;
	void RenderScreenTexture(RenderableSDLTexture* texture, int x, int y) const;
	void RenderScreenText(TTF_Font* font, const char* text, SDL_Color color, int x, int y) const;

	void DrawScreenRectangle(SDL_Rect* rect, int r, int g, int b, int a) const;
	void DrawScreenRectangleOutline(SDL_Rect* rect, int r, int g, int b, int a) const;

private :
	SDL_Renderer* _sdlRenderer;
	TextureController* _textureController;
	WorldPositionController* _worldPositionController;

	int _screenWidth;
	int _screenHeight;
	std::vector<std::vector<RenderableSDLTexture*>> _backgroundTiles;
};

