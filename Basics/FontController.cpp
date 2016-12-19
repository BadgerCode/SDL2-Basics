#include "FontController.h"



FontController::FontController()
{
	
}


FontController::~FontController()
{
}

bool FontController::PreloadFont(const char* name, int size)
{
	auto rawFont = TTF_OpenFont(name, size);

	if(rawFont == nullptr)
	{
		return false;
	}

	auto fontSizeMap = _loadedFonts.find(name);
	if(fontSizeMap == _loadedFonts.end())
	{
		_loadedFonts[name] = std::map<int, TTF_Font*>();
	}

	_loadedFonts[name][size] = rawFont;
	return true;
}

TTF_Font* FontController::GetFont(const char* name, int size)
{
	auto fontSizeMap = _loadedFonts.find(name);
	if (fontSizeMap == _loadedFonts.end())
	{
		PreloadFont(name, size);
		fontSizeMap = _loadedFonts.find(name);
		if (fontSizeMap == _loadedFonts.end())
		{
			return nullptr;
		}
	}

	auto rawFont = fontSizeMap->second.find(size);
	if(rawFont == fontSizeMap->second.end())
	{
		PreloadFont(name, size);
		rawFont = fontSizeMap->second.find(size);
		if (rawFont == fontSizeMap->second.end())
		{
			return nullptr;
		}
	}

	return rawFont->second;
}
