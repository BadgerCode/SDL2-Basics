#include "TextureController.h"

TextureController::TextureController(SDL_Renderer* sdlRenderer)
{
	_sdlRenderer = sdlRenderer;
}

TextureController::~TextureController()
{
}

bool TextureController::PreloadTexture(const std::string& str)
{
	auto rawTexture = IMG_LoadTexture(_sdlRenderer, str.c_str());
	//TODO: What if texture fails to load?
	if (rawTexture == nullptr)
	{
		return false;
	}

	_loadedTextures.insert(std::make_pair(str, rawTexture));

	return true;
}

SDLTexture* TextureController::GetTexture(const std::string& str)
{
	auto foundTexture = _loadedTextures.find(str);
	if(foundTexture == _loadedTextures.end())
	{
		PreloadTexture(str);
		foundTexture = _loadedTextures.find(str);
		if (foundTexture == _loadedTextures.end())
		{
			return nullptr;
		}
	}

	auto rawTexture = foundTexture->second;
	int width, height;
	SDL_QueryTexture(rawTexture, nullptr, nullptr, &width, &height);
	return new SDLTexture(rawTexture, width, height);
}
