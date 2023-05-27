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

class gameOver 
{

public:
	gameOver();
	virtual ~gameOver();

	//Accessor
	const bool runningOver() const;

	//Functions
	void overPollEvents();
	void renderOverWindow();
	void renderOverText();
	void setPoints(unsigned punkte);

private:

	//Variables
	unsigned points;

	//Window
	RenderWindow* overWindow;
	VideoMode videoMode;
	Event over;

	//Resources
	Font overFont1;

	//Text
	Text uiOverText;


	//private Functions
	void initOverWindow();
	void initOverFonts();
	void initOverText();
};