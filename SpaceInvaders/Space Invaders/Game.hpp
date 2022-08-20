#pragma once
#include "Stage.cpp"
#include <ctime>

class Game
{
public:
	Game();
	virtual ~Game();

	const bool running() const;

	void update();
	void render();
private:
	const int WIDTH = 800, HEIGHT = 600;
	sf::RenderWindow* window;
	sf::View view;
	sf::Event ev;
	Stage upRend;
	void initVariables();
	void initWindow();
	void pollEvents();

};