#pragma once

#include <SFML/Graphics.hpp>
#include "Ground.cpp"
#include "Animation.cpp"
#include <iostream>
class CollisionAndGround 
{
public:
	sf::Vector2f pos_player = { 250,50 };
	Ground tile1;
	std::vector<Ground> ground;
	sf::RectangleShape box_player;
	Animation* anim = new Animation("assets/player");
	float tamX, tamY;
	void initGround()
	{
		ground.push_back(tile1);

		ground[0].setGround(400, 300, "assets/Tiles/Tile1.png");
	}

	void verify_playerCollision()
	{
		for (auto &e : ground)
		{
			if (pos_player.x + tamX < e.posX
				&& pos_player.y + tamY > e.posY && pos_player.y < e.posY + e.tamY ||
				pos_player.x > e.posX + e.tamX
				&& pos_player.y + tamY > e.posY && pos_player.y < e.posY + e.tamY)
			{
				std::cout << "FORA!\n";
			}
			else if (pos_player.x + tamX > e.posX
				&& pos_player.y + tamY < e.posY && pos_player.y < e.posY + e.tamY ||
				pos_player.x < e.posX + e.tamX
				&& pos_player.y + tamY < e.posY && pos_player.y < e.posY + e.tamY
				||
				pos_player.x + tamX > e.posX
				&& pos_player.y > e.posY + e.tamY ||
				pos_player.x < e.posX + e.tamX
				&& pos_player.y > e.posY + e.tamY
				)
			{
				std::cout << "DENTRO\n";
			}
		}
	}
};