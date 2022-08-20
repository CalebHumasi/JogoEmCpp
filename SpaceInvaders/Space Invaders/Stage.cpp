#pragma once
#include <fstream>
#include <string>
#include "SpriteManager.cpp"
#include "Entity.cpp"
#include "Enemy1.cpp"
#include "Enemy2.cpp"
#include "Enemy3.cpp"
#include "Player.cpp"
#include "Explosao.cpp"
#include "Disco.cpp"

struct Timer1
{
	unsigned short actualTime{ 0 };
	unsigned const short limitimer{ 40 };
};
struct Block
{
private:
	sf::Vector2f position;
	sf::Vector2f tam;
	sf::Sprite spr_block;
public:
	Block(sf::Texture& texture) { spr_block.setTexture(texture); spr_block.setScale({ 3, 3 });
		tam.x = spr_block.getLocalBounds().width * 3; tam.y = spr_block.getLocalBounds().height * 3;}
	void setPosition(sf::Vector2f position) { this->position = position; this->spr_block.setPosition(position); }
	sf::FloatRect getBounds() { return sf::FloatRect(position.x, position.y, tam.x, tam.y); }
	sf::Sprite& getSprite() { return spr_block; }
};
class Stage : public SpriteManager
{
public:
	Stage()
	{
		if (!sb_explosion.loadFromFile("sounds/explosion.wav")) std::cout << "ERROR!\n";
		if (!sb_hit.loadFromFile("sounds/hit.wav")) std::cout << "ERROR!\n";
		snd_explosion.setBuffer(sb_explosion);
		snd_explosion.setVolume(30);

		snd_hit.setBuffer(sb_hit);
		snd_hit.setVolume(50);

		player.init(txtr_player, txtr_shoot );
		if (!font.loadFromFile("fonts/RetroFont.ttf")) std::cout << "ERROR!\n";
		txt_score.setFont(font);
		txt_score.setCharacterSize(22);
		txt_score.setFillColor(sf::Color::Cyan);
		txt_score.setString("Score: " + std::to_string(score));
		txt_gameOver.setFont(font);
		txt_gameOver.setCharacterSize(26);
		txt_gameOver.setFillColor(sf::Color::Red);
		txt_gameOver.setString("GAME OVER!");
		txt_gameOver.setPosition({ static_cast<float>(WIDTH / 2 - 125), static_cast<float>(HEIGHT / 2)});

		txt_win.setFont(font);
		txt_win.setCharacterSize(28);
		txt_win.setFillColor(sf::Color::Green);
		txt_win.setString("YOU WIN!");
		txt_win.setPosition({ static_cast<float>(WIDTH / 2 - 125), static_cast<float>(HEIGHT / 2) });

		txt_menu.setFont(font);
		txt_menu.setCharacterSize(30);
		txt_menu.setFillColor(sf::Color::Cyan);
		txt_menu.setString("PRESS ENTER!!");
		txt_menu.setPosition({ static_cast<float>(WIDTH / 2 - 175), static_cast<float>(HEIGHT -100) });

		txt_gameEnd.setFont(font);
		txt_gameEnd.setCharacterSize(30);
		txt_gameEnd.setFillColor(sf::Color::Cyan);
		txt_gameEnd.setString("PRESS R!!");
		txt_gameEnd.setPosition({ static_cast<float>(WIDTH / 2 - 125), static_cast<float>(100) });

		txt_spaceInvaders.setFont(font);
		txt_spaceInvaders.setCharacterSize(35);
		txt_spaceInvaders.setFillColor(sf::Color::Yellow);
		txt_spaceInvaders.setString("SPACE INVADERS\nULTIMATE");
		txt_spaceInvaders.setPosition({ static_cast<float>(100), static_cast<float>(100) });

		for (float posX = 100; posX < 540 - 24; posX += 48)
		{
			for (float posY = 0; posY < 200; posY += 42)
			{
				int vez = rand() % 3 - 0;
				if (enemigos[vez] == '#')
				{
					enemies.push_back(enemy);
					enemies[enemies.size() - 1] = new Enemy1();
					enemies[enemies.size() - 1]->life = 3;
					enemies[enemies.size() - 1]->init({ posX, posY }, txtr_enemy);
				}
				else if (enemigos[vez] == '!')
				{
					enemies.push_back(enemy1);
					enemies[enemies.size() - 1] = new Enemy2();
					enemies[enemies.size() - 1]->life = 1;
					enemies[enemies.size() - 1]->init({ posX, posY }, txtr_enemy1);
				}
				else if (enemigos[vez] == '*')
				{
					enemies.push_back(enemy2);
					enemies[enemies.size() - 1] = new Enemy3();
					enemies[enemies.size() - 1]->life = 2;
					enemies[enemies.size() - 1]->init({ posX, posY }, txtr_enemy2);
				}
			}
		}
		float posY = 400;
		for (float posX = 20; posX < 200; posX += bloco.getBounds().width)
		{
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 2 });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 3 });
		}
		for (float posX = 300; posX < 480; posX += bloco.getBounds().width)
		{
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 2 });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 3 });
		}
		for (float posX = 580; posX < 760; posX += bloco.getBounds().width)
		{
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height });
			blocos.push_back(bloco);							  
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 2 });
			blocos.push_back(bloco);							  
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 3 });
		}
		spr_background.setTexture(txtr_background);
		spr_background.setScale({ 3,3 });
	}
	virtual ~Stage()
	{
		delete enemy;
		delete enemy1;
		delete enemy2;
		savePoints();
	}
	void update()
	{
		if (scene == "MENU")
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) scene = "GAME";
		}
		else if (scene == "GAME")
		{
			player.update();
			randomizer();
			verifyShootCollision();
			verifyEnemies();
			verifyShootEnemies();
			discoAleatorio();

			if (!explosoes.empty()) {
				for (unsigned short i = 0; i < explosoes.size(); i++)
				{
					explosoes[i].anim(explosion);
					if (explosoes[i].actualFrame == 4) explosoes.erase(explosoes.begin() + i);
				}
			}
		}
		else if (scene == "GAMEOVER")
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { reset(false); scene = "GAME"; }
			if (!explosoes.empty()) {
				explosoes[explosoes.size() -1].anim(explosion);
				if (explosoes[explosoes.size() - 1].actualFrame == 4) explosoes.erase(explosoes.end() - 1);
			}

		}
		else if (scene == "WIN")
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { reset(true); scene = "GAME"; }
		}
	}
	void render(sf::RenderWindow *i_window)
	{
		i_window->draw(spr_background);
		if (scene == "GAME")
		{
			player.render(i_window);
			for (Entity* e : enemies) e->render(i_window);
			for (Block& e : blocos) { i_window->draw(e.getSprite()); }
			if (!tirosEne.empty()) { for (const TiroEn& e : tirosEne) i_window->draw(e.tiro); }
			for (Explosao& e : explosoes) i_window->draw(e.sprite);
			if (!discos.empty()) { for (Disco& e : discos) i_window->draw(e.getSprite()); }
		}
		else if (scene == "GAMEOVER") { 
			i_window->draw(txt_gameOver); 
			if (!explosoes.empty()) { i_window->draw(explosoes[explosoes.size() - 1].sprite); }
		}
		else if (scene == "WIN") i_window->draw(txt_win);
		else if (scene == "MENU")
		{
			i_window->draw(txt_spaceInvaders);
			i_window->draw(txt_menu);
		}
		if (scene == "GAMEOVER" || scene == "WIN") i_window->draw(txt_gameEnd);
		i_window->draw(txt_score);
	}
private:
	float speed{ 1 };
	const char enemigos[4] = "!#*";
	std::string scene = "MENU";
	const int WIDTH = 800, HEIGHT = 600;
	unsigned short timerN { 0 };
	unsigned const short limitimerN {750};
	int score {0};
	int maxScore{ 0 };
	sf::Font font;
	sf::Text txt_score;
	sf::Text txt_gameOver;
	sf::Text txt_win;
	sf::Text txt_menu;
	sf::Text txt_gameEnd;
	sf::Text txt_spaceInvaders;
	Timer1 timeShot;
	Player player;
	Block bloco{ txtr_tile1 };
	Disco disco{ txtr_disco };
	std::vector<Block> blocos;
	std::vector<Entity*> enemies;
	std::vector<TiroEn> tirosEne;
	std::vector<Explosao> explosoes;
	std::vector<Disco> discos;
	Enemy1* enemy = new Enemy1();
	Enemy2* enemy1 = new Enemy2();
	Enemy3* enemy2 = new Enemy3();
	sf::Sprite spr_background;
	std::ofstream armazena_pontos;
	std::ifstream le_pontos;
	sf::SoundBuffer sb_explosion, sb_hit;
	sf::Sound snd_explosion, snd_hit;

	void savePoints()
	{
		std::string pontos;
		le_pontos.open("SCORE.txt");
		if (score > maxScore) maxScore = score;
		
		if (le_pontos.is_open())
		{
			while (std::getline(le_pontos, pontos))
			{
				if (maxScore > std::stoi(pontos))
				{
					armazena_pontos.open("SCORE.txt");
					armazena_pontos << maxScore;
					armazena_pontos.close();
					break;
				}
			}
		}
		else
			std::cout << "NAO FOI POSSIVEL LER O ARQUIVO!";
	
		le_pontos.close();
		armazena_pontos.close();
	}
	void randomizer()
	{
		if (timeShot.actualTime < timeShot.limitimer)
			timeShot.actualTime++;
		else
		{
			timeShot.actualTime = 0;
			if (!enemies.empty())
			{
				int vez{ 0 };
				vez = rand() % static_cast<int>(enemies.size()) - 0;

				enemies[vez]->shoot(txtr_tiroEn, tirosEne);
			}
			else
				scene = "WIN";
		}
	}
	void discoAleatorio()
	{
		if (timerN < limitimerN)
			timerN++;
		else
		{
			timerN = 0;
			discos.push_back(disco);
			discos[discos.size() - 1].setPosition({static_cast<float>(WIDTH), 200});
		}

		if (!discos.empty())
		{
			for (unsigned char i = 0; i < discos.size(); i++)
			{
				discos[i].mov();
				sf::FloatRect rect = discos[i].getBounds();
				std::vector<Tiro>* tirosP = &player.getTiros();
				Tiro* tiroP;
				if (rect.left < 0)
				{
					discos.erase(discos.begin() + i);
					i--;
				}
				for (unsigned char j = 0; j < tirosP->size(); j++)
				{
					tiroP = &player.getTiros()[j];
					if (tiroP->getBounds().intersects(rect))
					{
						tirosP->erase(tirosP->begin() + j);
						discos.erase(discos.begin() + i);
						i--;
						score += 150;
						txt_score.setString("Score: " + std::to_string(score));
						explosoes.push_back(Explosao());
						explosoes[explosoes.size() - 1].init({ rect.left, rect.top }, explosion[0], snd_explosion);
						break;
					}
				}
			}
		}
	}
	void reset(bool winCondition)
	{
		enemies.clear();
		player.setPosition({ WIDTH / 2 - player.getBounds().width / 2, HEIGHT - player.getBounds().height});
		discos.clear();
		timerN = 0;
		if (!winCondition)
		{
			score = 0;
			txt_score.setString("Score: " + std::to_string(score));
		}
		for (float posX = 100; posX < 540 - 24; posX += 48)
		{
			for (float posY = 0; posY < 200; posY += 42)
			{
				int vez = rand() % 3 - 0;
				if (enemigos[vez] == '#')
				{
					enemies.push_back(enemy);
					enemies[enemies.size() - 1] = new Enemy1();
					enemies[enemies.size() - 1]->life = 3;
					enemies[enemies.size() - 1]->init({ posX, posY }, txtr_enemy);
				}
				else if (enemigos[vez] == '!')
				{
					enemies.push_back(enemy1);
					enemies[enemies.size() - 1] = new Enemy2();
					enemies[enemies.size() - 1]->life = 1;
					enemies[enemies.size() - 1]->init({ posX, posY }, txtr_enemy1);
				}
				else if (enemigos[vez] == '*')
				{
					enemies.push_back(enemy2);
					enemies[enemies.size() - 1] = new Enemy3();
					enemies[enemies.size() - 1]->life = 2;
					enemies[enemies.size() - 1]->init({ posX, posY }, txtr_enemy2);
				}
			}
		}
		blocos.clear();
		float posY = 400;
		for (float posX = 20; posX < 200; posX += bloco.getBounds().width)
		{
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 2 });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 3 });
		}
		for (float posX = 300; posX < 480; posX += bloco.getBounds().width)
		{
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 2 });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 3 });
		}
		for (float posX = 580; posX < 760; posX += bloco.getBounds().width)
		{
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 2 });
			blocos.push_back(bloco);
			blocos[blocos.size() - 1].setPosition({ posX, posY + bloco.getBounds().height * 3 });
		}
		speed = 1;
		explosoes.clear();
		player.getTiros().clear();
		tirosEne.clear();
	}

	void verifyShootCollision()
	{
		if (!player.getTiros().empty())
		{
			std::vector<Tiro>* tiros = &player.getTiros();
			Tiro* tiro;
			for (unsigned short i = 0; i < tiros->size(); i++)
			{
				tiro = &player.getTiros()[i];
				if (tiro->canChange)
				{
					sf::FloatRect rect = player.getBounds();
					tiro->tiro.setPosition({ rect.left + rect.width / 2 - tiro->getBounds().width / 2, rect.top});
					tiro->canChange = false;
				}
				tiro->update();
				if (tiro->getPos().y < 0)
				{
					tiros->erase(tiros->begin() + i);
					i--;
				}
				else
				{
					bool canVerify = true;
					for (unsigned short j = 0; j < blocos.size(); j++)
					{
						if (tiro->getBounds().intersects(blocos[j].getBounds()))
						{
							tiros->erase(tiros->begin() + i);
							blocos.erase(blocos.begin() + j);
							canVerify = false;
							i--;
							break;
						}
					}
					if (canVerify) 
					{
						for (unsigned short j = 0; j < enemies.size(); j++)
						{
							sf::FloatRect rectEn = enemies[j]->getBounds();
							if (rectEn.intersects(tiro->getBounds()))
							{
								tiros->erase(tiros->begin() + i);

								enemies[j]->life--;
								snd_hit.play();
								if (enemies[j]->life <= 0)
								{
									explosoes.push_back(Explosao());
									explosoes[explosoes.size() - 1].init({rectEn.left, rectEn.top}, explosion[0], snd_explosion);

									std::string nameBro = enemies[j]->getName();
									if (nameBro == "EN1") score += 25;
									else if (nameBro == "EN2") score += 75;
									else if (nameBro == "EN3") score += 50;
									
									if (this->score > this->maxScore) this->maxScore = this->score;
									enemies.erase(enemies.begin() + j);
									speed += 0.1f;
									
									txt_score.setString("Score: " + std::to_string(score));
									j--;
								}
								i--;
								break;
							}
						}
					
					}
				}
			}
		}
	}
	void verifyEnemies()
	{
		for (Entity *e : enemies)
		{
			sf::FloatRect rect = e->getBounds();
			std::string name = e->getName();
			if (name == "EN1")
				e->update(txtr_enemy, speed);
			else if (name == "EN2")
				e->update(txtr_enemy1, speed);
			else if (name == "EN3")
				e->update(txtr_enemy2, speed);

			if (rect.top + rect.height > HEIGHT - player.getBounds().height) scene = "GAMEOVER";
		}
		for (Entity* e : enemies)
		{
			sf::FloatRect rect = e->getBounds();
			if (rect.left < 0)
			{
				e->setRight(true);
				for (Entity* i : enemies)
				{
					i->setRight(true);
					i->walkOneTile();
				}
				return;
			}
			else if (rect.left + rect.width > WIDTH)
			{
				for (Entity* i : enemies)
				{
					i->setRight(false);
					i->walkOneTile();
				}
				return;
			}
		}
	}
	void verifyShootEnemies()
	{
		if (!tirosEne.empty())
		{
			for (unsigned short i = 0; i < tirosEne.size(); i++)
			{
				tirosEne[i].update();
				sf::FloatRect rect = tirosEne[i].getBounds();

				if (rect.top + rect.height > HEIGHT)
				{
					tirosEne.erase(tirosEne.begin() + i);
					i--;
				}
				else if (rect.intersects(player.getBounds()))
				{
					tirosEne.erase(tirosEne.begin() + i);
					if (this->score > this->maxScore) this->maxScore = this->score;
					scene = "GAMEOVER";
					explosoes.push_back(Explosao());
					sf::FloatRect rectP = player.getBounds();
					explosoes[explosoes.size() - 1].init({ rectP.left, rectP.top }, explosion[0], snd_explosion);
					i--;
				}
				else
				{
					for (unsigned short j = 0; j < blocos.size(); j++)
					{
						if (rect.intersects(blocos[j].getBounds()))
						{
							tirosEne.erase(tirosEne.begin() + i);
							blocos.erase(blocos.begin() + j);
							i--;
							break;
						}
					}
				}
			}
		}
	}
};
