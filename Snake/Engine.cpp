#include "Engine.h"

Engine::Engine() 
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}
Engine::~Engine()
{
	delete this->window;
}

//Accessors
const bool Engine::running() const
{
	return this->window->isOpen();
}

const bool Engine::getEndGame() const
{
	return this->endGame;
}





//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


//Functions
void Engine::spawnEnemy()
{

	//Spawns enemies and adds ot to the Vector
	
	this->initEnemy();
	this->enemies.push_back(this->enemy);


}

void Engine::pollEvents()
{
	//Event baby
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

void Engine::updateMousePositions()
{
	/*
	@return void

	Updates the mous positions:
	- Mouse position relative to window (Vector 2i)
	*/
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Engine::updateText()
{
	std::stringstream ss;

	ss <<this->points << std::endl << this->health;

	this->uiText.setString(ss.str());
}

void Engine::updateEnemies()
{
	/*
		Updates the enemy spawn timer and spawans enemies 
		when the total amount of enemies is smaller than the maximum.
		Moves the enemy downwoards
		Removes the enemies at the edge of the screen.	//TODO
	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else this->enemySpawnTimer += 1.f;
	}

	//Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 3.f);

		if (this->enemies[i].getPosition().y + this->enemies[i].getSize().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}
	}
	//Check if holding click
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gain points
					if (this->enemies[i].getFillColor() == Color::Magenta)
					{
						this->points += 10;
					} else if(this->enemies[i].getFillColor() == Color::Blue)
					{
						this->points += 7;
					}
					else if(this->enemies[i].getFillColor() == Color::Cyan)
					{
						this->points += 5;
					}
					else if(this->enemies[i].getFillColor() == Color::Yellow)
					{
						this->points += 3;
					}
					else if(this->enemies[i].getFillColor() == Color::Green)
					{
						this->points += 1;
					}
	
					std::cout << "P unkte: " << this->points << std::endl;

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
		
	}
	else this->mouseHeld = false;
}


void Engine::update()
{
	this->pollEvents();

	if (!this->endGame)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}

	//Game ending condition
	if (this->health <= 0) this->endGame = true;
}

void Engine::renderText(RenderTarget& target)
{
	target.draw(this->uiText);
}

void Engine::renderEnemies(RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Engine::render()
{
	/*
		@return void
		- clear old frame
		- render objects
		- display frame in the window
	*/
		this->window->clear(Color(153,153,153,1));
		
	//Draw the Game
		this->renderText(*this->window);

		this->renderEnemies(*this->window);

		this->window->display();
}

unsigned Engine::getPoints()
{
	return this->points;
}



//------------------------------------------------------------------------------------------------------------------------------------------------------------



//private Functions
void Engine::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->health = 20;
}

void Engine::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new RenderWindow(this->videoMode, "ClickToKill", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}

void Engine::initEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),		//Adaption to enemy size in case of the reference to the top left corner
		0.f					//rand only takes an Integer, so static_cast<int> safely converts the argument into an integer - but we wanna have a float, so we convert it back afterwards
	);

	//Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(Vector2f(20.f, 20.f));
		this->enemy.setFillColor(Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(Vector2f(40.f, 40.f));
		this->enemy.setFillColor(Color::Blue);
		break;
	case 2:
		this->enemy.setSize(Vector2f(60.f, 60.f));
		this->enemy.setFillColor(Color::Cyan);
		break;
	case 3:
		this->enemy.setSize(Vector2f(80.f, 80.f));
		this->enemy.setFillColor(Color::Yellow);
		break;
	case 4:
		this->enemy.setSize(Vector2f(100.f, 100.f));
		this->enemy.setFillColor(Color::Green);
		break;
	default:
		this->enemy.setSize(Vector2f(100.f, 100.f));
		this->enemy.setFillColor(Color::Red);
		break;
	}
	
//	this->enemy.setScale(0.5f, 0.5f);
	this->enemy.setOutlineColor(Color::Black);
	this->enemy.setOutlineThickness(10.f);


}

void Engine::initFonts()
{
	if (this->font1.loadFromFile("Fonts/1942.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void Engine::initText()
{
	this->uiText.setPosition(Vector2f(330.f, 110.f));
	this->uiText.setFont(this->font1);
	this->uiText.setCharacterSize(120);
	this->uiText.setFillColor(Color::White);
	this->uiText.setString("NONE");
}


//Game Over stuff ---------------------------------------------------------------------------------------------------------------------

