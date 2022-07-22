#include "Game.h"

void Game::initVariables() { this->window = nullptr; lost = false; }

void Game::initWindow()
{
	this->video.height = 600;
	this->video.width = 900;
	this->window = new sf::RenderWindow(this->video, "NaveGame", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}
void Game::initFundo()
{
	if (!this->texture.loadFromFile("assets/Background/GameOver.png")) std::cout << "ERROR!";
	this->sprite.setTexture(this->texture);
	this->sprite.setScale({ 0.9f, 0.9f });
	if (!this->font.loadFromFile("fonts/RetroFont.ttf")) std::cout << "ERROR!";
	this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setString("SCORE: " + std::to_string(this->points));
	this->text.setFillColor(sf::Color::Green);
}
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFundo();
}

Game::~Game() { delete this->window; }

const bool Game::running() const{ return this->window->isOpen(); }
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
void Game::setDificuldade(unsigned short speed_of_game)
{
	this->multiplo = speed_of_game;
	unsigned short bla;
	std::cin >> bla;
	level.setLimitTimer(bla);
}
void Game::updateCollision()
{
	for (int i = 0; i < level.enemies.size(); i++)
	{
		if (player->box_player.getGlobalBounds().intersects(level.enemies[i].enemy_box.getGlobalBounds()))
		{
			if (player->can_turbo)
				lost = true;
			else
			{
				level.enemies.erase(level.enemies.begin() + i);
				this->points += 10;
				this->text.setString("SCORE: " + std::to_string(this->points));
			}
		}
	}
	for (int i = 0; i < level.enemies.size(); i++)
	{
		for (int j = 0; j < player->tiros.size(); j++)
		{
			if (level.enemies[i].enemy_box.getGlobalBounds().intersects(player->tiros[j].tiro.getGlobalBounds()))
			{
				level.enemies.erase(level.enemies.begin() + i);
				player->tiros.erase(player->tiros.begin() + j);
				this->points += 10;
				this->text.setString("SCORE: " + std::to_string(this->points));
				break;
			}
		}
	}
}
void Game::updateSpeed()
{
	if (!player->can_turbo)
		level.mult = multiplo;
	else
		level.mult = multiplo - 1;
}

void Game::reset()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && this->lost)
	{
		player->setPosition_player();
		while (!level.enemies.empty()) level.enemies.pop_back();
		while (!player->tiros.empty()) player->tiros.pop_back();
		this->lost = false;
		if (this->points > this->maxPoints) this->maxPoints = this->points;
		this->points = 0;
		this->text.setString("SCORE: " + std::to_string(this->points));
		player->reset_timers();
	}
}
void Game::savePoints()
{
	std::string pontos;
	this->le_pontos.open("pontos.txt");
	if (this->points > this->maxPoints) this->maxPoints = this->points;
	if (this->le_pontos.is_open())
	{
		while (std::getline(this->le_pontos, pontos))
		{
			if (this->maxPoints > std::stoi(pontos))
			{
				this->armazena_pontos.open("pontos.txt");
				this->armazena_pontos << this->maxPoints;
				this->armazena_pontos.close();
				break;
			}
		}
	}
	else
		std::cout << "ERRO, NAO FOI POSSIVEL LER O ARQUIVO!";

	this->le_pontos.close();
	this->armazena_pontos.close();
}

void Game::update()
{
	this->pollEvents();
	if (!this->lost){this->level.updateEnemies();
					 this->player->updatePlayer();
					 this->updateCollision();
					 this->updateSpeed(); }
	else this->reset();
}
void Game::render()
{
	this->window->clear();

	if (!this->lost){ this->level.renderEnemiesStars(window); 
					  this->player->renderPlayer(window);
					  this->window->draw(this->text); }
	else this->window->draw(sprite);
	this->window->display();
}
