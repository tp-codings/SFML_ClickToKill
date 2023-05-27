#pragma once
#include <vector>
#include <ctime>
#include <sstream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include <iostream>

using namespace sf;
//Class that acts like the game engine

class Engine
{
public:

	//Constructors / Deconstructors
	Engine();
	virtual ~Engine();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;


	//Functions
	void spawnEnemy();

	void pollEvents();

	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();

	unsigned getPoints();

private:

	//Variables
	
	//Window
	RenderWindow *window;
	VideoMode videoMode;
	Event ev;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Resources
	Font font1;

	//Text
	Text uiText;

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<RectangleShape> enemies;
	RectangleShape enemy;

	//Private Functions
	void initVariables();
	void initWindow();
	void initEnemy();
	void initFonts();
	void initText();

};

