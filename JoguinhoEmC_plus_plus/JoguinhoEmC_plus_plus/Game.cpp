#include "Game.h"

//Init variables
void Game::initVariables()
{
	this->window = nullptr;
}
//Initialize window
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Primeiro jogo", sf::Style::Titlebar | sf::Style::Close);

	this->camera.setSize({ 900,700 });
	this->window->setFramerateLimit(60);
}

//Start before the first frame
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->world.initGround();
	this->world.initEnemies();
	this->player.initPlayer({ 35,60 });
}
//Destroy the window after the user close the window;
Game::~Game()
{
	delete this->window;
}
//Accessors
const bool::Game::running() const
{
	return this->window->isOpen();
}
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}
//Update Player Collision
void Game::updatePlayerCollision()
{
	this->player.up = this->collision.collisionDetectionUp(this->player.boxPlayer, this->world.objetos);
	this->player.down = this->collision.collisionDetectionDown(this->player.boxPlayer, this->world.objetos);
	this->player.left = this->collision.collisionDetectionLeft(this->player.boxPlayer, this->world.objetos);
	this->player.right = this->collision.collisionDetectionRight(this->player.boxPlayer, this->world.objetos);
}
void Game::updatePlayerGrounded()
{
	this->player.collisionGround = this->collision.getCollisionGround(this->player.boxPlayer, this->world.objetos);
	this->player.isGrounded = this->collision.canJumpAttack(this->player.boxPlayer, this->world.objetos);
}
void Game::updatePlayerCWEnemies() 
{
	for (int i = 0; i < world.enemies.size(); i++)
	{
		if (this->collision.getCollisionBox(player.boxPlayer, world.enemies[i].boxCollider) && !player.isDamaged)
		{
			player.isDamaged = true;
			player.vida.setSize({ player.vida.getSize().x - 20, player.vida.getSize().y });
			if (player.vida.getSize().x <= 0)
			{
				player.setPosition({ 200, 0 });
				player.vida.setSize({ 200,30 });
			}
		}
	}
	
}
void Game::updateEnemiesCADistance()
{
	for (int i = 0; i < world.enemies.size(); i++)
	{
		for (int j = 0; j < player.tiros.size(); j++)
		{
			if (this->collision.getCollisionBox(player.tiros[j].tiro, world.enemies[i].boxCollider) && !world.enemies[i].isDamaged)
			{
				this->player.tiros.erase(player.tiros.begin() + j);
				this->world.enemies[i].health--;
				if (this->world.enemies[i].health == 0)
					this->world.enemies.erase(world.enemies.begin() + i);
				else
					this->world.enemies[i].isDamaged = true;
			}
		}
	}
}
void Game::updateSwordCollision()
{
	for (int i = 0; i < this->world.enemies.size(); i++)
	{
		if (this->collision.getCollisionBox(this->world.enemies[i].boxCollider, this->player.boxSword) && this->player.anim.isVisible
			&& !world.enemies[i].isDamaged)
		{
			this->world.enemies[i].health--;
			if (this->world.enemies[i].health == 0)
				this->world.enemies.erase(world.enemies.begin() + i);
			else
				this->world.enemies[i].isDamaged = true;
		}
	}
}
void Game::updateEnemiesCollision()
{
	for (int i = 0; i < this->world.enemies.size(); i++)
	{
		this->world.enemies[i].isGrounded = this->collision.getCollisionGroundOther(this->world.enemies[i].boxCollider, this->world.objetos);
	}
}
void Game::updatePitCheckEnemy()
{
	for (int i = 0; i < this->world.enemies.size(); i++)
	{
		this->world.enemies[i].havePitD = this->collision.getCollisionGroundOther(this->world.enemies[i].getShapeD(), this->world.objetos);
		this->world.enemies[i].havePitE = this->collision.getCollisionGroundOther(this->world.enemies[i].getShapeE(), this->world.objetos);
	}
}
void Game::updateWallCheckEnemy()
{
	for (int i = 0; i < this->world.enemies.size(); i++)
	{
		this->world.enemies[i].haveWallD = this->collision.getCollisionGroundOther(this->world.enemies[i].getWallD(), this->world.objetos);
		this->world.enemies[i].haveWallE = this->collision.getCollisionGroundOther(this->world.enemies[i].getWallE(), this->world.objetos);
	}
}

//Update the game
void Game::update()
{
	this->pollEvents();
	this->player.updatePlayer();
	this->updatePlayerCollision();
	this->updatePlayerGrounded();
	this->updatePlayerCWEnemies();
	this->updateSwordCollision();
	if (!world.enemies.empty()) 
	{
		this->updateEnemiesCollision();
		this->updatePitCheckEnemy();
		this->updateWallCheckEnemy();
		this->world.updateEnemies();
		this->updateEnemiesCADistance();
	}
	this->window->setView(camera);
	this->camera.setCenter(player.boxPlayer.getPosition().x + player.boxPlayer.getSize().x / 2,
		player.boxPlayer.getPosition().y + player.boxPlayer.getSize().y / 2);
}
//Render the game
void Game::render()
{
	/*
		-clear old frame
		-render objects
		-display frame in window
		-Renders the game objects
	*/
	this->window->clear();
	//Draw game objects
	this->player.renderPlayer(window);
	this->world.renderEnemies(window);
	this->world.renderGround(window);
	//Display frame window
	this->window->display();
}