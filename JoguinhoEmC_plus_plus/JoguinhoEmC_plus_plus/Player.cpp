#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "AnimationPlayer.cpp"
#include "World.cpp"
#include "CollisionDetection.cpp"

struct Tiro 
{
public:
	unsigned short speed = 0;
	unsigned short timer = 0;
	bool isRight;
	bool canChange = true;
	sf::RectangleShape tiro;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos;

	void initTiro()
	{
		tiro.setSize({ 15,15 });
		tiro.setFillColor(sf::Color::Cyan);
		if (!texture.loadFromFile("assets/Fire_Ball/ball.png"))
			std::cout << "ERRO!";
		sprite.setTexture(texture);
		sprite.setScale({ 1,1 });
	}
	void startShoot(sf::RectangleShape player)
	{
		pos.x = player.getPosition().x + player.getSize().x / 2 - 7;
		pos.y = player.getPosition().y + player.getSize().y / 2 - 7;
		tiro.setPosition({ pos.x, pos.y });
		sprite.setPosition({ tiro.getPosition().x, tiro.getPosition().y });
	}
	void updateTiro()
	{
		tiro.setPosition({ pos.x, pos.y });
		sprite.setPosition({ tiro.getPosition().x, tiro.getPosition().y });
		if (isRight)
			pos.x -= 15;
		else
			pos.x += 15;

		timer++;
	}
};

class Player
{
private:
	sf::Vector2f posP = {200,40};
	World world;
	unsigned short timer = 0, limitimer = 20;
	unsigned short timerShoot = 0, timeToShoot = 10;
	bool canShoot = true;
public:
	float gravity = 0;
	AnimationPlayer anim;
	Tiro shoot;
	std::vector<Tiro> tiros;
	sf::RectangleShape boxPlayer, boxSword;
	sf::RectangleShape vida;
	bool up = false, down = false;
	bool right = false, left = false;
	bool collisionGround = false, isGrounded = false;
	bool isDamaged = false;
	void initPlayer(sf::Vector2f size)
	{
		anim.initAnim();
		boxPlayer.setSize({ size.x, size.y });
		boxPlayer.setPosition({posP.x,posP.y});
		boxPlayer.setFillColor(sf::Color::Red);
		boxSword.setSize({ 45,20 });
		boxSword.setFillColor(sf::Color::Transparent);
		vida.setSize({200,30});
		vida.setFillColor(sf::Color::Red);
		shoot.initTiro();
	}
	void setPosition(sf::Vector2f posP)
	{
		this->posP = posP;
	}
	void playerMov()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !right)
		{
			if(!anim.isAttacking)
				anim.sprite.setScale({ 2,2 });
			anim.isWalking = true;
			if (!anim.isAttacking || anim.isAttacking && !isGrounded)
				posP.x += 6;
		}
		else if (right)
			posP.x -= 2;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !left)
		{
			if(!anim.isAttacking)
				anim.sprite.setScale({ -2,2 });
			anim.isWalking = true;
			if (!anim.isAttacking || anim.isAttacking && !isGrounded)
				posP.x -= 6;
		}
		else if (left)
			posP.x += 2;

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isGrounded)
		{
			posP.x += 0;
			anim.isWalking = false;
			anim.inAir = false;
		}

		if (!isGrounded)
			anim.inAir = true;
		else
		{
			posP.x += 0;
			anim.inAir = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !anim.isAttacking)
			anim.isAttacking = true;

		if (down && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			posP.y -= 1;
		else
			posP.y += gravity;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && canShoot)
		{
			canShoot = false;
			tiros.push_back(shoot);
		}
	}
	void shootTiro()
	{
		if (!tiros.empty())
		{
			for (int i = 0; i < tiros.size(); i++)
			{
				if (anim.sprite.getScale().x > 0 && tiros[i].canChange)
				{
					tiros[i].startShoot(boxPlayer);
					tiros[i].isRight = false;
					tiros[i].canChange = false;
				}
				else if (anim.sprite.getScale().x < 0 && tiros[i].canChange)
				{
					tiros[i].startShoot(boxPlayer);
					tiros[i].isRight = true;
					tiros[i].canChange = false;
				}
			}
		}
	}
	void playerIsDamaged()
	{
		if (isDamaged)
		{
			if (timer < limitimer)
			{
				timer++;
				if (timer >= limitimer)
				{
					isDamaged = false;
					timer = 0;
				}
			}
		}
	}
	void verifyIsGrounded()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded && !up)
		{
			gravity = -11;
		}
		else if (up)
		{
			gravity = 6;
		}
		else if (collisionGround)
			gravity = 0;
		else
			if (gravity < 10)
				gravity += 0.5f;
	}
	void updateLados()
	{
		if (anim.sprite.getScale().x == -2)
			anim.sprite.setPosition({ posP.x + boxPlayer.getSize().x,posP.y });
		else
			anim.sprite.setPosition({ posP.x,posP.y });
	}
	void updateSword()
	{
		if (anim.sprite.getScale().x > 0)
		{
			anim.spriteSword.setPosition({ posP.x + 45, posP.y + 2 });
			boxSword.setPosition({ posP.x + 65, posP.y + 5 });
			anim.spriteSword.setScale({ 2,2 });
		}
		else
		{
			anim.spriteSword.setPosition({ posP.x - 10, posP.y + 2 });
			boxSword.setPosition({ posP.x - 75, posP.y + 5 });
			anim.spriteSword.setScale({ -2,2 });
		}
	}
	void timerShootBro()
	{
		if (!canShoot)
		{
			if (timerShoot < timeToShoot)
				timerShoot++;
			else
			{
				canShoot = true;
				timerShoot = 0;
			}
		}
	}
	void updateTiros()
	{
		if (!tiros.empty())
		{
			for (int i = 0; i < tiros.size(); i++)
			{
				tiros[i].updateTiro();
				if (tiros[i].timer > 30)
				{
					tiros.erase(tiros.begin() + i);
				}
			}
		}
	}
	void updatePlayer()
	{
		playerMov();
		playerIsDamaged();
		anim.updateAnimations(gravity);
		boxPlayer.setPosition({ posP.x,posP.y });
		vida.setPosition(boxPlayer.getPosition().x - 400, boxPlayer.getPosition().y - 300);
		updateSword();
		updateLados();
		timerShootBro();
		shootTiro();
		updateTiros();
		verifyIsGrounded();
	}
	void renderPlayer(sf::RenderWindow *window)
	{
		window->draw(anim.sprite);
		if (anim.isVisible) { window->draw(anim.spriteSword); window->draw(boxSword); }
		window->draw(boxPlayer);
		window->draw(vida);
		renderTiro(window);
	}
	void renderTiro(sf::RenderWindow* window)
	{
		if (!tiros.empty())
		{
			for (int i = 0; i < tiros.size(); i++)
			{
				window->draw(tiros[i].sprite);
			}
		}
	}
};