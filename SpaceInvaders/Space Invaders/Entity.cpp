#pragma once

#include <SFML/Graphics.hpp>
#include "TiroEn.cpp"
#include <iostream>

class Entity
{	
protected:
	sf::Vector2f position;
	sf::Vector2f tam;
	bool right = true;
	sf::Sprite sprite;
	unsigned char timer{ 0 };
	unsigned const char limitimer{ 15 };
	unsigned char actualFrame{ 0 };
public:
	unsigned char life{ 0 };
	virtual void update(sf::Texture texture[2], const float speed) = 0;
	virtual void render(sf::RenderWindow* window) = 0;
	virtual void walkOneTile() = 0;
	virtual void init(sf::Vector2f position, sf::Texture texture[2]) = 0;
	virtual void setRight(bool right) = 0;
	virtual void shoot(sf::Texture& txtr, std::vector<TiroEn> &tiros) = 0;
	virtual sf::FloatRect getBounds() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual std::string getName() = 0;
};