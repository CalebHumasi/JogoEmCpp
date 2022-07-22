#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

//Tiro
struct Tiro
{
private:
	unsigned short speed;
public:
	sf::RectangleShape tiro;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f posT;
	bool can_change;
	Tiro(sf::Vector2f size, unsigned short speed)
	{
		this->speed = speed;
		if (!texture.loadFromFile("assets/Player/tiro.png"))
			std::cout << "ERROR!";
		sprite.setTexture(texture);
		tiro.setSize(size);
		sprite.setScale({ 3,3 });
		can_change = true;
	}

	void initTiro(sf::RectangleShape player)
	{
		posT.y = player.getPosition().y + player.getSize().y / 2;
		posT.x = player.getPosition().x + player.getSize().x;
		can_change = false;
	}
	void updateTiro(bool can_turbo)
	{
		if (can_turbo) posT.x += speed;
		else posT.x -= speed / 2;

		tiro.setPosition({posT.x, posT.y});
		sprite.setPosition(tiro.getPosition());
	}
};

//Player
class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos_player = {50, 50};
	Tiro* tiro = new Tiro({18,10}, 12);
	unsigned short speed, timer = 0, limitimer = 15;
	unsigned short timer1 = 0, limitimer1 = 120;
	unsigned short timer2 = 0;
	bool can_shoot = true, timing = false;

	void playerActions()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && box_player.getPosition().x > 0)
			pos_player.x -= speed;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && box_player.getPosition().x < 852)
			pos_player.x += speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && box_player.getPosition().y > 0)
			pos_player.y -= speed;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && box_player.getPosition().y < 579)
			pos_player.y += speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && can_shoot && can_turbo)
		{
			tiros.push_back(*tiro);
			can_shoot = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && can_turbo && !timing)
			can_turbo = false;
	}
	void ienumerator_turbo()
	{
		if (!can_turbo)
		{
			if (!texture.loadFromFile("assets/Player/NaveTurbo.png"))
				std::cout << "Error!";
			if (timer1 < limitimer1)
				timer1++;
			else
			{
				can_turbo = true;
				timer1 = 0;
				if (!texture.loadFromFile("assets/Player/Nave.png"))
					std::cout << "Error!";
				sprite.setTexture(texture);
				timing = true;
			}
		}
		
		if (timing)
		{
			if (timer2 < limitimer1 * 3)
				timer2++;
			else
			{
				timing = false;
				timer2 = 0;
			}
		}
	}
	void ienumerator_shot()
	{
		if (!can_shoot)
		{
			if (timer < limitimer)
				timer++;
			else
			{
				can_shoot = true;
				timer = 0;
			}
		}
	}
	void initTiros()
	{
		if (!tiros.empty())
		{
			for (int i = 0; i < tiros.size(); i++)
			{
				if (tiros[i].can_change) tiros[i].initTiro(box_player);
			}
		}
	}
	void updateTiros()
	{
		if (!tiros.empty())
		{
			for (int i = 0; i < tiros.size(); i++)
			{
				tiros[i].updateTiro(can_turbo);
				if (tiros[i].posT.x > 890 || tiros[i].posT.x < -50) tiros.erase(tiros.begin() + i);
			}
		}
	}
	void renderTiros(sf::RenderWindow* window)
	{
		if (!tiros.empty())
		{
			for (int i = 0; i < tiros.size(); i++)
				window->draw(tiros[i].sprite);
		}
	}
public:
	std::vector<Tiro> tiros;
	sf::RectangleShape box_player;
	bool can_turbo = true;

	Player(sf::Vector2f size, short speed)
	{
		if (!texture.loadFromFile("assets/Player/NaveTurbo.png"))
			std::cout << "Error!";
		sprite.setTexture(texture);
		if (!texture.loadFromFile("assets/Player/Nave.png"))
			std::cout << "Error!";
		sprite.setTexture(texture);

		this->box_player.setSize({ size.x, size.y });
		this->sprite.setScale({ 1,1 });
		this->speed = speed;
	}
	void setPosition_player()
	{
		pos_player.x = 50;
		pos_player.y = 50;
	}
	void reset_timers()
	{
		timer2 = 0;
		timing = false;
	}

	void updatePlayer()
	{
		box_player.setPosition(pos_player);
		sprite.setPosition(box_player.getPosition());
		playerActions();
		ienumerator_shot();
		ienumerator_turbo();
		initTiros();
		updateTiros();
	}
	void renderPlayer(sf::RenderWindow *window)
	{
		window->draw(sprite);
		renderTiros(window);
	}
};
//601 linhas, joguinho simples :v