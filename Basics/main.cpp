#include "GameEngineFactory.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	auto engine = GameEngineFactory::Create("Game basics", 400, 400);

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
