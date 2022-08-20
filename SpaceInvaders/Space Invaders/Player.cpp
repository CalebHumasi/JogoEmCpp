#pragma once
#include "Tiro.cpp"
#include <SFML/Audio.hpp>
struct Timer
{
	unsigned short actualTime{ 0 };
	unsigned const short limitimer { 20 };
};
class Player
{
public:

	void init(sf::Texture &texture, sf::Texture &tiro)
	{
		player.setTexture(texture);

		player.setScale({ 3,3 });
		tam.x = player.getLocalBounds().width * 3;
		tam.y = player.getLocalBounds().height * 3;
		player.setPosition({WIDTH / 2 - tam.x / 2, HEIGHT - tam.y});
		this->tiro.init(tiro);

		if (!sb_shoot.loadFromFile("sounds/shoot.wav")) std::cout << "ERROR!\n";
		snd_shoot.setBuffer(sb_shoot);
		snd_shoot.setVolume(30);
	}
	void update()
	{
		mov();
		shootTiming();
	}
	void render(sf::RenderWindow* i_window)
	{
		i_window->draw(player);

		if (!tiros.empty()) { for (Tiro& e : tiros) i_window->draw(e.tiro);  }
	}
	void setPosition(sf::Vector2f position) 
	{
		player.setPosition(position);
	}

	std::vector<Tiro> &getTiros() { return tiros; }
	sf::FloatRect getBounds() { return sf::FloatRect(player.getPosition().x, player.getPosition().y, tam.x, tam.y); }
private:
	sf::Sprite player;
	std::vector<Tiro> tiros;
	sf::Vector2f tam;
	sf::SoundBuffer sb_shoot;
	sf::Sound snd_shoot;
	Tiro tiro;
	Timer timer;
	const float speed = 4;
	const int WIDTH = 800, HEIGHT = 600;
	bool isShooting = false;
	
	void mov()
	{
		float posX = player.getPosition().x;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if(posX > 0) player.move(-speed, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if(posX < WIDTH - tam.x) player.move(speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && !isShooting)
		{
			tiros.push_back(tiro);
			snd_shoot.play();
			isShooting = true;
		}
	}
	void shootTiming()
	{
		if (isShooting)
		{
			if(timer.actualTime < timer.limitimer)timer.actualTime++;
			else { isShooting = false; timer.actualTime = 0; }
		}
	}
};