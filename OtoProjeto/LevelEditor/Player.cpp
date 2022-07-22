#include "Player.h"

void::Player::initPlayer()
{
	this->box_player.setSize({ 30,56 });
	this->initGround();
	this->tamX = this->box_player.getSize().x;
	this->tamY = this->box_player.getSize().y;
}

void::Player::movPlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->pos_player.x -= this->speed;
		this->anim->sprite.setScale({ -4,4 });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->pos_player.x += this->speed;
		this->anim->sprite.setScale({ 4,4 });
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->pos_player.y -= this->speed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->pos_player.y += this->speed;

	this->anim->isRunning = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	this->box_player.setPosition(this->pos_player);
	this->anim->sprite.setPosition({ pos_player.x + tamX / 2,pos_player.y + tamY / 2 });

}

void::Player::updatePlayer()
{
	this->movPlayer();
	this->verify_playerCollision();
	this->anim->animRun();
}

void::Player::renderPlayer(sf::RenderWindow* window)
{
	window->draw(box_player);
	window->draw(anim->sprite);
}