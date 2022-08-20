#pragma once
#include <SFML/Graphics.hpp>

class Disco
{
private:
	sf::Vector2f position;
	sf::Vector2f tam;
	sf::Sprite spr_disco;
public:
	Disco(sf::Texture& texture) 
	{
		spr_disco.setTexture(texture);
		spr_disco.setScale({ 3,3 });
		tam.x = spr_disco.getLocalBounds().width * 3;
		tam.y = spr_disco.getLocalBounds().height * 3;
	}
	void setPosition(sf::Vector2f position) { this->position = position; spr_disco.setPosition(position); }
	void mov() { position.x -= 4; spr_disco.setPosition(position); }

	sf::Sprite &getSprite() { return spr_disco; }
	sf::FloatRect getBounds() { return sf::FloatRect(position.x, position.y, tam.x, tam.y); }
};