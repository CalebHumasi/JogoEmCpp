#include <SFML/Graphics.hpp>
#include <iostream>

class TiroEn
{
public:
	bool canChange = true;
	sf::Sprite tiro;
	sf::Vector2f speed;
	void init(sf::Texture& texture, sf::Vector2f speed, sf::Vector2f position)
	{
		tiro.setTexture(texture);
		tiro.setScale({ 3,3 });
		tam.x = tiro.getLocalBounds().width * 3;
		tam.y = tiro.getLocalBounds().height * 3;
		tiro.setPosition(position);
		this->speed = speed;
	}
	void update()
	{
		tiro.move(speed.x, speed.y);
	}
	sf::FloatRect getBounds() { return sf::FloatRect(tiro.getPosition().x, tiro.getPosition().y, tam.x, tam.y); }
	sf::Vector2f getPos() { return tiro.getPosition(); }
private:
	sf::Vector2f tam;
};