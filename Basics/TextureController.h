#pragma once
#include "SDLTexture.h"
#include <map>

class TextureController
{
public:
	TextureController(SDL_Renderer* sdlRenderer);
	~TextureController();

	bool PreloadTexture(const std::string &str);
	SDLTexture* GetTexture(const std::string &str);

private:
	std::map<std::string, SDL_Texture*> _loadedTextures;
	SDL_Renderer* _sdlRenderer;
};

