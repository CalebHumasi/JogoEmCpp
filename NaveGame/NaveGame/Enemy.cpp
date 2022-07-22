#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy 
{
private:
	sf::Vector2f pos_enemy;
	sf::Texture texture;
	unsigned short timer = 0, limitimer = 35;
public:
	sf::Sprite sprite;
	bool can_change;
	bool cima_baixo, can_zigzag;
	sf::RectangleShape enemy_box;
	Enemy(sf::Vector2f size, std::string imagem, bool can_zigzag)
	{
		enemy_box.setSize(size);
		pos_enemy.x = 900;
		can_change = true;

		if (!texture.loadFromFile(imagem))
			std::cout << "ERROR!";

		sprite.setTexture(texture);
		sprite.setScale({ 4,4 });
		cima_baixo = true;
		this->can_zigzag = can_zigzag;
	}


	void initPositionY(unsigned short posY) { pos_enemy.y = posY; can_change = false; }
	
	void mov_vertically()
	{
		timer++;
		if (timer > limitimer)
		{
			timer = 0;
			cima_baixo = !cima_baixo;
		}
		if (can_zigzag)
		{
			if (cima_baixo == true)
				pos_enemy.y += 5;
			else
				pos_enemy.y -= 5;
		}
	}
	void updateEnemy(unsigned int vel)
	{
		pos_enemy.x -= 8 * vel;
		mov_vertically();
		enemy_box.setPosition(pos_enemy);
		sprite.setPosition(pos_enemy);
	}
};