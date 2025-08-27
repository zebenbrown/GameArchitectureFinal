#include <MemoryTracker.h>
#include <EventSystem.h>

#include "Game.h"
#include <SFML/Graphics.hpp>

//Recieved permission to use the assignement 5 code of Christopher Eichert as a base for this project.

int main()
{
	//Create and init Event System
	EventSystem::createInstance();
	EventSystem::getInstance()->init();

	////Create and init game
	Game::createInstance();
	Game::getInstance()->init();


	//Call game loop here
	Game::getInstance()->doLoop();

	//Clean up game
	Game::destroyInstance();

	//Clean up event system
	EventSystem::destroyInstance();

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;
}