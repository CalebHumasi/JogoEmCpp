#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Entity
{
private:
	Player player;
	sf::RectangleShape shape;
	sf::Texture texture;
	void drawGround(sf::RenderWindow* window);
public:
	void initEntities();


	void updateEntities();
	void renderEntities(sf::RenderWindow* window);
};

