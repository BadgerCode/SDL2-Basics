#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "RenderableSDLTexture.h"
#include <vector>
#include "TextureController.h"

class RenderController
{
public:
	RenderController(SDL_Renderer* renderer, TextureController* textureController, int screenWidth, int screenHeight);
	~RenderController();

	void ClearScreen() const;
	void UpdateScreen() const;
	void DrawBackground() const;
	void PreloadBackground();

	void RenderTexture(RenderableSDLTexture* texture, int x, int y) const;
	void RenderText(TTF_Font* font, const char* text, SDL_Color color, int x, int y) const;

	void DrawRectangle(SDL_Rect* rect, int r, int g, int b, int a) const;
	void DrawRectangleOutline(SDL_Rect* rect, int r, int g, int b, int a) const;

private :
	SDL_Renderer* _sdlRenderer;
	TextureController* _textureController;

	int _screenWidth;
	int _screenHeight;
	std::vector<std::vector<RenderableSDLTexture*>> _backgroundTiles;
};

