#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Animation
{
private:
	unsigned short timer = 0;
	const unsigned short limitimer = 8;
	unsigned short actualFrame = 0;
public:
	sf::Texture running[4];
	sf::Texture iddle;
	sf::Texture shoot;
	sf::Sprite sprite;
	bool isRunning = false;

	Animation(std::string caminho)
	{
		if (!running[0].loadFromFile(caminho + "/run1.png"))
			std::cout << "ERROR!";
		if (!running[1].loadFromFile(caminho + "/run2.png"))
			std::cout << "ERROR!";
		if (!running[2].loadFromFile(caminho + "/run3.png"))
			std::cout << "ERROR!";

		if (!running[3].loadFromFile(caminho + "/run2.png"))
			std::cout << "ERROR!";

		if (!iddle.loadFromFile(caminho + "/run2.png"))
			std::cout << "ERROR!";
		
		if (!shoot.loadFromFile(caminho + "/shoot.png"))
			std::cout << "ERROR!";

		sprite.setTexture(iddle);
		sprite.setScale({ 4,4 });
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}
	void animRun()
	{
		if (isRunning)
		{
			if (actualFrame == 0)
				sprite.setTexture(running[0]);

			if (timer < limitimer)
				timer++;
			else
			{
				actualFrame++;
				if (actualFrame == 4) actualFrame = 0;
				sprite.setTexture(running[actualFrame]);

				timer = 0;
			}
		}
		else
		{
			sprite.setTexture(iddle);
			actualFrame = 0;
			timer = 0;
		}
	}
};