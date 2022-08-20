#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Tiro
{
public:
	bool canChange = true;
	sf::Sprite tiro;
	void init(sf::Texture& texture)
	{
		tiro.setTexture(texture);
		tiro.setScale({ 3,3 });
		tam.x = tiro.getLocalBounds().width * 3;
		tam.y = tiro.getLocalBounds().height * 3;
	}
	void update()
	{
		tiro.move(0, -6);
	}
	sf::FloatRect getBounds() { return sf::FloatRect(tiro.getPosition().x, tiro.getPosition().y, tam.x, tam.y); }
	sf::Vector2f getPos() { return tiro.getPosition(); }
private:
	sf::Vector2f tam;
};