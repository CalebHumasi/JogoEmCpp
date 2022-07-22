#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "Player.cpp"
#include "World.cpp"

class Game
{
private:
	//Variables and window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::View camera;
	Player player;
	World world;
	CollisionDetection collision;
	//Private Functions

	void initVariables();
	void initWindow();
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void pollEvents();
	void updatePlayerCollision();
	void updatePlayerCWEnemies();
	void updatePlayerGrounded();
	void updateSwordCollision();
	void updateEnemiesCollision();
	void updateEnemiesCADistance();
	void updatePitCheckEnemy();
	void updateWallCheckEnemy();

	//Update
	void update();
	//Render
	void render();
};
//1063 linhas de código aaaaaaaaaaaaaaaaaaaa