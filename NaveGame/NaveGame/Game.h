#pragma once
#include <SFML/Graphics.hpp>
#include "Player.cpp"
#include "LevelManager.cpp"
#include <fstream>
#include <string>
class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode video;
	sf::Event ev;
	sf::Texture texture;
	sf::Sprite sprite;
	Player* player = new Player({ 48, 21 }, 7);
	LevelManager level;
	sf::Font font; sf::Text text;
	std::ofstream armazena_pontos;
	std::ifstream le_pontos;
	bool lost;
	unsigned int maxPoints = 0;
	unsigned int points = 0;
	unsigned short multiplo = 2;

	//Private Functions
	void initVariables();
	void initWindow();
	void initFundo();
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;


	//Functions
	void setDificuldade(unsigned short vel_of_game);
	void pollEvents();
	void updateCollision();
	void updateSpeed();
	void reset();
	void savePoints();

	void update();
	void render();
};