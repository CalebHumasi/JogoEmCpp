#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Ground 
{
private:
	sf::Texture texture;
public:
	sf::Sprite sprite;
	float tamX, tamY;
	float posX, posY;
	bool is_inside;
	void setGround(const float posX, const float posY, std::string link)
	{
		if (!texture.loadFromFile(link))
			std::cout << "ERROR!";

		sprite.setTexture(texture);
		sprite.setScale({ 4,4 });

		sprite.setPosition(posX, posY);
		this->posX = posX;	
		this->posY = posY;

		tamX = sprite.getLocalBounds().width * 4;
		tamY = sprite.getLocalBounds().height * 4;
	}
	void draw(sf::RenderWindow *window)
	{
		window->draw(sprite);
	}
};