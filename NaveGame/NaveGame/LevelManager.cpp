#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Enemy.cpp"

struct Estrelas
{
public:
	bool can_change;
	sf::Vector2f pos_estrela;
	sf::RectangleShape star;
	Estrelas(sf::Vector2f size)
	{
		star.setSize(size);
		can_change = true;
	}


	void initPositionY(unsigned short posY) { pos_estrela.y = posY; can_change = false; }
	void updateStar(unsigned int vel)
	{
		pos_estrela.x -= 13 * vel;
		star.setPosition(pos_estrela);
	}
};
class LevelManager 
{
private:
	Enemy* enemy = new Enemy({ 40,25 }, "assets/Enemy/Inimigo.png", false);
	Enemy* enemy1 = new Enemy({ 40,25 }, "assets/Enemy/Inimigo1.png", true);
	Estrelas* star = new Estrelas({ 5,5 });
	unsigned short timer = 0, limitimer = 15;
	unsigned short vez = 0;

	void spawnEnemies()
	{
		if (timer < limitimer)
			timer++;
		else
		{
			if (vez == 0) { enemies.push_back(*enemy); vez = 1; }
			else if (vez == 1) { enemies.push_back(*enemy1); vez = 0; }
			timer = 0;
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].can_change)
				enemies[i].initPositionY((rand() % static_cast<int>(600 - enemies[i].enemy_box.getSize().y)));
		}
		
	}
	void spawnStars()
	{

		for (int i = 0; i < stars.size(); i++)
		{
			if (stars[i].can_change)
				stars[i].initPositionY((rand() % static_cast<int>(600 - stars[i].star.getSize().y)));
		}
		
	}
	void movStars()
	{
		for (int i = 0; i < stars.size(); i++)
		{
			stars[i].updateStar(mult);
			if (stars[i].star.getPosition().x < -50)
			{
				stars[i].pos_estrela.x = 900;
				stars[i].initPositionY((rand() % static_cast<int>(600 - stars[i].star.getSize().y)));
			}
		}
	}
	void movEnemies()
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].updateEnemy(mult);
			if (enemies[i].enemy_box.getPosition().x < -50)
				enemies.erase(enemies.begin() + i);
		}
		
	}
public:
	std::vector<Enemy> enemies;
	std::vector<Estrelas> stars;
	unsigned short mult = 1;

	LevelManager()
	{
		for (int i = 0; i < 80; i++)
		{
			stars.push_back(*star);
			stars[i].pos_estrela.x = (rand() % static_cast<int>(900 - stars[i].star.getSize().x));
		}
	}

	void setLimitTimer(unsigned short limitimer){ this->limitimer = limitimer; }

	void updateEnemies()
	{
		spawnEnemies();
		spawnStars();
		movStars();
		movEnemies();
	}
	void renderEnemiesStars(sf::RenderWindow *window)
	{
		if (!enemies.empty())
		{
			for (auto& e : enemies)
				window->draw(e.sprite);
		}
		if (!stars.empty())
		{
			for (auto& e : stars)
				window->draw(e.star);
		}
	}
};