#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

class AnimationPlayer
{
private:
	unsigned short frames = 0;
	unsigned short timer = 0, limitimer = 5;

	unsigned short framesA = 0;
	unsigned short timerA = 0, limitimerA = 10;

public:
	bool isWalking = false, isAttacking = false, inAir = false;
	bool isVisible = false;
	sf::Texture texture, textureSword;
	sf::Sprite sprite, spriteSword;
	void initAnim()
	{
		if (!texture.loadFromFile("assets/Hugh_Attack/hugh_attack2.png"))
			std::cout << "ERROR!";
		sprite.setTexture(texture);
		sprite.setScale({ 2,2 });

		if (!textureSword.loadFromFile("assets/Hugh_Attack/hugh_attack3.png"))
			std::cout << "ERROR!";
		spriteSword.setTexture(textureSword);
		spriteSword.setScale({ 2,2 });
	}
	void iddleAnim()
	{
		if (!isAttacking && !inAir && !isWalking)
		{
			if (!texture.loadFromFile("assets/Hugh_Iddle/hugh_iddle.png"))
				std::cout << "ERROR!";
		}
	}
	void animWalk()
	{
		if (isWalking && !isAttacking)
		{
			if (frames == 0)
			{
				if (!texture.loadFromFile("assets/Hugh_Run/hugh_run1.png"))
					std::cout << "ERROR!";
			}
			if (timer < limitimer)
				timer++;
			else
			{
				frames++;
				switch (frames)
				{
				case 1:
					if (!texture.loadFromFile("assets/Hugh_Run/hugh_run2.png"))
						std::cout << "ERROR!";
					break;
				case 2:
					if (!texture.loadFromFile("assets/Hugh_Run/hugh_run3.png"))
						std::cout << "ERROR!";
					break;
				case 3:
					if (!texture.loadFromFile("assets/Hugh_Run/hugh_run4.png"))
						std::cout << "ERROR!";
					break;
				case 4:
					if (!texture.loadFromFile("assets/Hugh_Run/hugh_run5.png"))
						std::cout << "ERROR!";
					break;
				case 5:
					if (!texture.loadFromFile("assets/Hugh_Run/hugh_run6.png"))
						std::cout << "ERROR!";
					break;
				case 6:
					timer = 0;
					frames = 0;
				}
				timer = 0;
			}
		}
		else
		{
			timer = 0;
			frames = 0;
		}
	}
	void isInAir(float gravity)
	{
		if (inAir && !isAttacking)
		{
			if (gravity < 0)
			{
				if (!texture.loadFromFile("assets/Hugh_Jump/hugh_jump.png"))
					std::cout << "ERROR!";
			}
			else
			{
				if (!texture.loadFromFile("assets/Hugh_Jump/hugh_jump1.png"))
					std::cout << "ERROR!";
			}
		}
	}
	void attack()
	{
		if (isAttacking)
		{
			if (framesA == 0)
			{
				if (!texture.loadFromFile("assets/Hugh_Attack/hugh_attack1.png"))
					std::cout << "ERROR!";
			}
			if (timerA < limitimerA)
				timerA++;
			else
			{
				framesA++;
				switch (framesA)
				{
				case 1:
					if (!texture.loadFromFile("assets/Hugh_Attack/hugh_attack2.png"))
						std::cout << "ERROR!";

					isVisible = true;
					break;
				case 2:
					isAttacking = false;
					isVisible = false;
					framesA = 0;
				}
				timerA = 0;
			}
		}
		else
		{
			if (timerA != 0)
				timerA = 0;
			if (framesA != 0)
				framesA = 0;
		}
	}
	void updateAnimations(float gravity)
	{
		attack();
		iddleAnim();
		animWalk();
		isInAir(gravity);
	}
};
//OIA O TANTO DE CLASSE BIXO KKKKKKKKKK