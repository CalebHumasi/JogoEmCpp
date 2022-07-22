#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class CollisionDetection
{
private:
	//Player Detections

	//Pegando centro X do player
	float getCenterX(sf::RectangleShape player)
	{
		return player.getPosition().x + player.getSize().x / 2;
	}
	//Pegando centro Y do player
	float getCenterY(sf::RectangleShape player)
	{
		return player.getPosition().y + player.getSize().y / 2;
	}
	//Pegando metade do tamanho do player em X
	float getDivX(sf::RectangleShape player)
	{
		return player.getSize().x / 2;
	}
	//Pegando metade do tamanho do player em Y
	float getDivY(sf::RectangleShape player)
	{
		return player.getSize().y / 2;
	}
	//Chao Detections

	//Pegando centro X do chao
	float getCenterCX(int i, std::vector<sf::RectangleShape> blocos)
	{
		return blocos[i].getPosition().x + blocos[i].getSize().x / 2;
	}
	//Pegando centro Y do chao
	float getCenterCY(int i, std::vector<sf::RectangleShape> blocos)
	{
		return blocos[i].getPosition().y + blocos[i].getSize().y / 2;
	}
	//Pegando metade do tamanho do chao em X (serve para pegar as pontas do chao)
	float getDivCX(int i, std::vector<sf::RectangleShape> blocos)
	{
		return blocos[i].getSize().x / 2;
	}
	//Pegando metade do tamanho do chao em Y (bloco único)
	float getDivCY(int i, std::vector<sf::RectangleShape> blocos)
	{
		return blocos[i].getSize().y / 2;
	}
	//Pegando centro X do chao (bloco único)
	float getCenterCX(sf::RectangleShape agente)
	{
		return agente.getPosition().x + agente.getSize().x / 2;
	}
	//Pegando centro Y do chao (bloco único)
	float getCenterCY(sf::RectangleShape agente)
	{
		return agente.getPosition().y + agente.getSize().y / 2;
	}
	//Pegando metade do tamanho do chao em X (bloco único)
	float getDivCX(sf::RectangleShape agente)
	{
		return agente.getSize().x / 2;
	}
	//Pegando metade do tamanho do chao em Y (bloco único)
	float getDivCY(sf::RectangleShape agente)
	{
		return agente.getSize().y / 2;
	}
public:
	//VerifyIsGrounded
	bool canJumpAttack(sf::RectangleShape p, std::vector<sf::RectangleShape> b)
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (getCenterX(p) + 10 > getCenterCX(i, b) - getDivCX(i, b) && getCenterX(p) - 10 < getCenterCX(i, b) + getDivCX(i, b)
				&& getCenterY(p) + getDivY(p) - 20 < getCenterCY(i,b) - getDivCY(i,b)
				&& getCenterY(p) + getDivY(p) + 10 > getCenterCY(i,b) - getDivCY(i,b))
				return true;
		}
		return false;
	}
	//Get box player collision with ground boxes
	bool getCollisionGround(sf::RectangleShape p, std::vector<sf::RectangleShape> b)
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (getCenterX(p) + getDivX(p) - 8 > getCenterCX(i, b) - getDivCX(i,b) && getCenterX(p) + getDivX(p) -8 < getCenterCX(i,b) + getDivCX(i,b)
				&& getCenterY(p) + getDivY(p) >= getCenterCY(i, b) - getDivCY(i, b)
				&& getCenterY(p) - getDivY(p) <= getCenterCY(i, b) + getDivCY(i, b)
			||  getCenterX(p) - getDivX(p) + 8 < getCenterCX(i, b) + getDivCX(i, b) && getCenterX(p) - getDivX(p) + 8 > getCenterCX(i, b) - getDivCX(i, b)
				&& getCenterY(p) + getDivY(p) >= getCenterCY(i, b) - getDivCY(i, b)
				&& getCenterY(p) - getDivY(p) <= getCenterCY(i, b) + getDivCY(i, b))
				return true;
		}
		return false;
	}
	//CollisionGround with other entities
	bool getCollisionGroundOther(sf::RectangleShape p, std::vector<sf::RectangleShape> b)
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (getCenterX(p) + getDivX(p) > getCenterCX(i, b) - getDivCX(i, b) && getCenterX(p) + getDivX(p) < getCenterCX(i, b) + getDivCX(i, b)
				&& getCenterY(p) + getDivY(p) >= getCenterCY(i, b) - getDivCY(i, b)
				&& getCenterY(p) - getDivY(p) <= getCenterCY(i, b) + getDivCY(i, b)
				|| getCenterX(p) - getDivX(p) < getCenterCX(i, b) + getDivCX(i, b) && getCenterX(p) - getDivX(p) > getCenterCX(i, b) - getDivCX(i, b)
				&& getCenterY(p) + getDivY(p) >= getCenterCY(i, b) - getDivCY(i, b)
				&& getCenterY(p) - getDivY(p) <= getCenterCY(i, b) + getDivCY(i, b))
				return true;
		}
		return false;
	}
	//Get collision with something
	bool getCollisionBox(sf::RectangleShape p, sf::RectangleShape b)
	{
		if (getCenterX(p) + getDivX(p) > getCenterCX(b) - getDivCX(b) && getCenterX(p) + getDivX(p) < getCenterCX(b) + getDivCX(b)
			&& getCenterY(p) + getDivY(p) >= getCenterCY(b) - getDivCY(b)
			&& getCenterY(p) - getDivY(p) <= getCenterCY(b) + getDivCY(b)
		 || getCenterX(p) - getDivX(p) <= getCenterCX(b) + getDivCX(b) && getCenterX(p) - getDivX(p) > getCenterCX(b) - getDivCX(b)
			&& getCenterY(p) + getDivY(p) >= getCenterCY(b) - getDivCY(b)
			&& getCenterY(p) - getDivY(p) <= getCenterCY(b) + getDivCY(b))
			return true;
		else
			return false;
	}
	//Player collision up
	bool collisionDetectionUp(sf::RectangleShape p, std::vector<sf::RectangleShape> b)
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (getCenterY(p) - getDivY(p) < getCenterCY(i,b) + getDivCY(i,b) && getCenterY(p) - getDivY(p) > getCenterCY(i,b)
				&& getCenterX(p) + getDivX(p) - 7 > getCenterCX(i, b) - getDivCX(i, b)
				&& getCenterX(p) - getDivX(p) + 7 < getCenterCX(i, b) + getDivCX(i, b))
				return true;
		}
		return false;
	}
	//Player collision down
	bool collisionDetectionDown(sf::RectangleShape p, std::vector<sf::RectangleShape> b)
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (getCenterY(p) + getDivY(p) > getCenterCY(i, b) - getDivCY(i, b) && getCenterY(p) + getDivY(p) < getCenterCY(i, b)
				&& getCenterX(p) + getDivX(p) - 7 > getCenterCX(i, b) - getDivCX(i, b)
				&& getCenterX(p) - getDivX(p) + 7 < getCenterCX(i, b) + getDivCX(i, b))
				return true;
		}
		return false;
	}
	//player collision left
	bool collisionDetectionRight(sf::RectangleShape p, std::vector<sf::RectangleShape> b)
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (getCenterX(p) + getDivX(p) > getCenterCX(i,b) - getDivCX(i,b) && getCenterX(p) + getDivX(p) < getCenterCX(i,b)
				&& getCenterY(p) + getDivY(p) - 11 > getCenterCY(i,b) - getDivCY(i,b)
				&& getCenterY(p) - getDivY(p) + 11 < getCenterCY(i, b) + getDivCY(i, b))
				return true;
		}
		return false;
	}
	bool collisionDetectionLeft(sf::RectangleShape p, std::vector<sf::RectangleShape> b)
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (getCenterX(p) - getDivX(p) < getCenterCX(i, b) + getDivCX(i, b) && getCenterX(p) - getDivX(p) > getCenterCX(i, b)
				&& getCenterY(p) + getDivY(p) - 11 > getCenterCY(i, b) - getDivCY(i, b)
				&& getCenterY(p) - getDivY(p) + 11 < getCenterCY(i, b) + getDivCY(i, b))
				return true;
		}
		return false;
	}
};