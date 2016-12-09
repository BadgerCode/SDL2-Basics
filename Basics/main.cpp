#include "GameEngineFactory.h"
#include <iostream>
#include <string>
#include "SDLRendererFactory.h"
#include "SDLWindowFactory.h"
#include <ctime>

int main(int argc, char** argv)
{
	auto windowTitle = "Game basics";
	auto screenWidth = 1280;
	auto screenHeight = 720;

	// Initialise rand
	srand(static_cast<unsigned int>(time(nullptr)));

	// Create SDL dependencies
	auto sdlWindow = SDLWindowFactory::Create(windowTitle, screenWidth, screenHeight);
	auto sdlRenderer = SDLRendererFactory::Create(sdlWindow);

	if(sdlWindow == nullptr || sdlRenderer == nullptr)
	{
		std::cout << "SDL error: " << SDL_GetError() << std::endl;
		std::cout << "Press any key to continue." << std::endl;
		std::string c;
		getline(std::cin, c);
		return 0;
	}

	auto engine = GameEngineFactory::Create(sdlRenderer, screenWidth, screenHeight);
	engine->Start();
	return 0;
}
