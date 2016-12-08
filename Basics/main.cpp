#include "GameEngineFactory.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	srand(time(nullptr));
	auto engine = GameEngineFactory::Create("Game basics", 1280, 720);

	auto gameStarted = engine->Start();
	if(!gameStarted)
	{
		std::cout << "Engine error: " << engine->GetLastError() << std::endl;
		std::cout << "Press any key to continue." << std::endl;
		std::string c;
		getline(std::cin, c);
	}
	return 0;
}
