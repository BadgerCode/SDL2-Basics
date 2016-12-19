#pragma once
#include <map>
#include <SDL2/SDL_ttf.h>

class FontController
{
public:
	FontController();
	~FontController();

	bool PreloadFont(const char* name, int size);
	TTF_Font* GetFont(const char* name, int size);

private:
	std::map<std::string, std::map<int, TTF_Font*>> _loadedFonts;
};

