#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class Enemy
{
private:
	float cdDamaged = 15;
	unsigned short timer = 0;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape pitCheckE, pitCheckD;
	sf::RectangleShape wallCheckE, wallCheckD;
	unsigned int time = 0, frames = 0, limitimer = 12;
	unsigned short speed = 2;
public:
	unsigned int health = 0;
	unsigned short gravity = 0;
	bool isGrounded = false;
	bool right = false;
	bool havePitD = false, havePitE = false;
	bool haveWallD = false, haveWallE = false;
	sf::Vector2f position;
	sf::RectangleShape boxCollider;
	bool isDamaged = false;

	void initEnemies(unsigned int health, sf::Vector2f position)
	{
		this->health = health;
		this->position = position;
		boxCollider.setSize({45,115});
		boxCollider.setFillColor(sf::Color::Transparent);
		pitCheckD.setSize({ 10,10 });
		pitCheckE.setSize({ 10,10 });
		wallCheckD.setSize({ 10,10 });
		wallCheckE.setSize({ 10,10 });
		pitCheckD.setFillColor(sf::Color::Red);
		pitCheckE.setFillColor(sf::Color::Red);

		wallCheckD.setFillColor(sf::Color::Red);
		wallCheckE.setFillColor(sf::Color::Red);

		if (!texture.loadFromFile("assets/Axe_Armor/axe_armor4.png"))
			std::cout << "ERROR!";

		sprite.setTexture(texture);
		sprite.setScale({2,2});
	}

	sf::Sprite getSprite(){ return sprite; }
	sf::RectangleShape getShapeD() { return pitCheckD; } sf::RectangleShape getShapeE() { return pitCheckE; }
	sf::RectangleShape getWallD() { return wallCheckD; } sf::RectangleShape getWallE() { return wallCheckE; }

	void enemyFunctions()
	{
		animationEnemy();
		pitCheckD.setPosition({ boxCollider.getPosition().x + boxCollider.getSize().x, boxCollider.getPosition().y + boxCollider.getSize().y });
		pitCheckE.setPosition({ boxCollider.getPosition().x - pitCheckE.getSize().x, boxCollider.getPosition().y + boxCollider.getSize().y });
		wallCheckD.setPosition({ boxCollider.getPosition().x + boxCollider.getSize().x, boxCollider.getPosition().y + boxCollider.getSize().y / 2 });
		wallCheckE.setPosition({ boxCollider.getPosition().x - wallCheckE.getSize().x, boxCollider.getPosition().y + boxCollider.getSize().y / 2 });
		position.y += gravity;
		if (!right)
		{
			sprite.setScale({ 2,2 });
			sprite.setPosition({ boxCollider.getPosition().x, boxCollider.getPosition().y });
			position.x -= speed;
		}
		else
		{
			sprite.setScale({ -2,2 });
			sprite.setPosition({ boxCollider.getPosition().x + boxCollider.getSize().x, boxCollider.getPosition().y});
			position.x += speed;
		}

		if (isGrounded)
			gravity = 0;
		else
			gravity = 3;

		if (!havePitE && isGrounded)
			right = true;
		else if (!havePitD && isGrounded)
			right = false;

		if (haveWallE && isGrounded)
			right = true;
		else if (haveWallD && isGrounded)
			right = false;

		if (isDamaged)
		{
			if (timer < cdDamaged)
			{
				timer++;
			}
			else
			{
				isDamaged = false;
				timer = 0;
			}
		}
	}
	void animationEnemy()
	{
		if (time < limitimer)
		{
			time++;
			if (frames == 0)
			{
				if (!texture.loadFromFile("assets/Axe_Armor/axe_armor1.png"))
					std::cout << "ERROR!";
				sprite.setTexture(texture);
			}
		}
		else
		{
			time = 0;
			frames++;
			switch (frames)
			{
			case 1:
				if (!texture.loadFromFile("assets/Axe_Armor/axe_armor2.png"))
					std::cout << "ERROR!";
				sprite.setTexture(texture);
				break;
			case 2:
				if (!texture.loadFromFile("assets/Axe_Armor/axe_armor3.png"))
					std::cout << "ERROR!";
				sprite.setTexture(texture);
				break;
			case 3:
				if (!texture.loadFromFile("assets/Axe_Armor/axe_armor4.png"))
					std::cout << "ERROR!";
				sprite.setTexture(texture);
				break;
			case 4:
				frames = 0;
				break;
			}
		}
	}
};
//Script of the enemy :v (script do inimigo :v)