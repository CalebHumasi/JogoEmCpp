#include "Game.hpp"

void::Game::initVariables() { this->window = nullptr; }

void Game::initWindow()
{
	this->view.setSize({ static_cast<float>(WIDTH), static_cast<float>(HEIGHT) });
	this->view.setCenter({ static_cast<float>(WIDTH / 2), static_cast<float>(HEIGHT / 2) });
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "SPACE INVADERS", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setView(view);
}
Game::Game()
{
	this->initVariables();
	this->initWindow();
}
Game::~Game()
{
	delete this->window;
}

const bool::Game::running() const { return this->window->isOpen(); }

void::Game::pollEvents()
{
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}
void::Game::update()
{
	this->pollEvents();
	this->upRend.update();
}
void::Game::render()
{
	this->window->clear(sf::Color(0, 0, 30));
	this->upRend.render(this->window);
	this->window->display();
}