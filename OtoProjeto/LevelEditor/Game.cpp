#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
}
void Game::initWindow()
{
	this->video.width = 900;
	this->video.height = 600;
	this->window = new sf::RenderWindow(video, "MALANDRO :)", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}


Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->entities.initEntities();
}
Game::~Game()
{
	delete this->window;
}
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (ev.type)
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

void Game::update()
{
	this->pollEvents();
	this->entities.updateEntities();
}
void Game::render()
{
	this->window->clear();
	this->entities.renderEntities(window);
	this->window->display();
}