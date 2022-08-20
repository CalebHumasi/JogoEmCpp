#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class SpriteManager
{
protected:
	sf::Texture txtr_player, txtr_shoot;
	sf::Texture txtr_enemy[2], txtr_enemy1[2];
	sf::Texture txtr_enemy2[2];
	sf::Texture txtr_tiroEn;
	sf::Texture txtr_background;
	sf::Texture txtr_tile1;
	sf::Texture txtr_disco;
	sf::Texture explosion[4];

	SpriteManager()
	{
		if(!txtr_player.loadFromFile("assets/player/player.png")) std::cout << "ERROR!\n";
		if(!txtr_shoot.loadFromFile("assets/player/shoot.png")) std::cout << "ERROR!\n";
		if(!txtr_enemy[0].loadFromFile("assets/enemies/EN1_1.png")) std::cout << "ERROR!\n";
		if(!txtr_enemy1[0].loadFromFile("assets/enemies/EN2_1.png")) std::cout << "ERROR!\n";
		if (!txtr_enemy[1].loadFromFile("assets/enemies/EN1_2.png")) std::cout << "ERROR!\n";
		if (!txtr_enemy1[1].loadFromFile("assets/enemies/EN2_2.png")) std::cout << "ERROR!\n";

		if (!txtr_enemy2[0].loadFromFile("assets/enemies/EN3_1.png")) std::cout << "ERROR!\n";
		if (!txtr_enemy2[1].loadFromFile("assets/enemies/EN3_2.png")) std::cout << "ERROR!\n";
		

		if (!txtr_tiroEn.loadFromFile("assets/enemies/shoot.png")) std::cout << "ERROR!\n";
		if (!txtr_background.loadFromFile("assets/background.png")) std::cout << "ERROR!\n";
		if (!txtr_tile1.loadFromFile("assets/tile1.png")) std::cout << "ERROR!\n";
		if (!txtr_disco.loadFromFile("assets/enemies/DISCO.png")) std::cout << "ERROR!\n";
		if (!explosion[0].loadFromFile("assets/enemies/END_1.png")) std::cout << "ERROR!\n";
		if (!explosion[1].loadFromFile("assets/enemies/END_2.png")) std::cout << "ERROR!\n";
		if (!explosion[2].loadFromFile("assets/enemies/END_3.png")) std::cout << "ERROR!\n";
		if (!explosion[3].loadFromFile("assets/enemies/END_4.png")) std::cout << "ERROR!\n";
	}
};