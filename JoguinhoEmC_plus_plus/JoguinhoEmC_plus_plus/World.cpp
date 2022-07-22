#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "Enemy.cpp";

class World
{
public:
	sf::RectangleShape objeto;
	Enemy enemy;

	std::vector<Enemy> enemies;
	std::vector<sf::RectangleShape> objetos;
	
	void initGround()
	{
		for (int i = 0; i < 5; i++){objetos.push_back(objeto);}

		objetos[0].setPosition({ -100, 300 });
		objetos[0].setSize({ 400,50 });

		objetos[1].setPosition({ 200, 500 });
		objetos[1].setSize({ 300,100 });

		objetos[2].setPosition({ 500, 400 });
		objetos[2].setSize({ 150,150 });

		objetos[3].setPosition({ 100, 250 });
		objetos[3].setSize({ 50,50 });
		objetos[3].setFillColor(sf::Color::Red);

		objetos[4].setPosition({ -100, 150 });
		objetos[4].setSize({ 50,50 });
		objetos[4].setFillColor(sf::Color::Yellow);
	}
	void initEnemies()
	{	
		for (int i = 0; i < 3; i++){enemies.push_back(enemy);}
		
		enemies[0].initEnemies(3, {400,300});
		enemies[1].initEnemies(3, { 100,0 });
		enemies[2].initEnemies(3, { 550,200 });
	}
	void updateEnemies()
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].boxCollider.setPosition({enemies[i].position.x,enemies[i].position.y});
			enemies[i].enemyFunctions();
		}
	}
	void renderGround(sf::RenderWindow *window)
	{
		for (int i = 0; i < this->objetos.size(); i++) {window->draw(objetos[i]);}
	}
	void renderEnemies(sf::RenderWindow *window)
	{
		for (int i = 0; i < this->enemies.size(); i++) 
		{
			window->draw(enemies[i].boxCollider);
			window->draw(enemies[i].getSprite());
		}
	}
};