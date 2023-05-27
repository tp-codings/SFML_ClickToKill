#include "gameOver.h"

//Constructor and Deconstructor
gameOver::gameOver()
{
	this->initOverWindow();
	this->initOverFonts();
	this->initOverText();
}

gameOver::~gameOver()
{
	delete this->overWindow;
}


//Accessor
const bool gameOver::runningOver() const
{
	return this->overWindow->isOpen();
}

//Functions
void gameOver::overPollEvents()
{
	//Event baby
	while (this->overWindow->pollEvent(this->over))
	{
		switch (this->over.type)
		{
		case Event::Closed:
			this->overWindow->close();
			break;
		case Event::KeyPressed:
			if (this->over.key.code == Keyboard::Escape)
			{
				this->overWindow->close();
			}
			break;
		}
	}
}


void gameOver::renderOverText()
{
	std::stringstream ss;

	ss << "GAAAAAME" << std::endl << "OOOOOVER" << std::endl << std::endl << "  " << this->points;
	this->uiOverText.setString(ss.str());
}

void gameOver::setPoints(unsigned punkte)
{
	this->points = punkte;
}


void gameOver::renderOverWindow()
{
	this->overWindow->clear(Color(153, 153, 153, 1));
	this->renderOverText();
	this->overWindow->draw(this->uiOverText);
	this->overWindow->display();
}


//private Functions----------------------------------------------------------------------------------------------
void gameOver::initOverWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->overWindow = new RenderWindow(this->videoMode, "GAME OVER", Style::Titlebar | Style::Close);
	this->overWindow->setFramerateLimit(60);
}

void gameOver::initOverFonts()
{
	if(this->overFont1.loadFromFile("Fonts/1942.ttf")) 
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
	}
}

void gameOver::initOverText()
{
	this->uiOverText.setPosition(Vector2f(170.f, 60.f));
	this->uiOverText.setFont(this->overFont1);
	this->uiOverText.setCharacterSize(90);
	this->uiOverText.setFillColor(Color( 129,0,0,255 ));
	this->uiOverText.setString("NONE");
}


