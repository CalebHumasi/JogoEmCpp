#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode video;
	sf::Event ev;
	Entity entities;

//Private Functions
	void initVariables();
	void initWindow();
public:
	Game();
	virtual ~Game();

//Accessors
	const bool running() const;

//Functions
	void pollEvents();
	void update();
	void render();
};