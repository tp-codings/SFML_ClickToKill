#include "Engine.h"
#include "gameOver.h"

using namespace sf;

int main() 
{
	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init Engine
	Engine Engine;

	//Game Loop

	while (Engine.running() && !Engine.getEndGame()) 
	{

		//Update
		Engine.update();

		//Render
		Engine.render();
	}
	
	gameOver gameOver;

	gameOver.setPoints(Engine.getPoints());
	while (gameOver.runningOver())
	{
		gameOver.overPollEvents();
		gameOver.renderOverWindow();
	}

	std::cout << std::endl << "GAAAAAAAME OOOOOOOVER" << std::endl << std::endl << "Erreichte Punkte: " << Engine.getPoints() << std::endl << std::endl;
	//End of Game
	return 0;
}