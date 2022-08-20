#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Explosao
{
private:
	unsigned short time{0};
	unsigned short limitimer {5};
	sf::Sound snd_explosion;
public:
	sf::Sprite sprite;
	unsigned short actualFrame{ 0 };
	void anim(sf::Texture texture[4])
	{
		sprite.setTexture(texture[actualFrame]);
		if (time < limitimer)
			time++;
		else
		{
			time = 0;
			if (actualFrame <= 3)
				actualFrame++;
		}
	}
	void init(sf::Vector2f position, sf::Texture &texture, sf::Sound &snd_explosion)
	{
		sprite.setPosition(position);
		sprite.setTexture(texture);
		sprite.setScale({3,3});
		snd_explosion.play();
	}
};