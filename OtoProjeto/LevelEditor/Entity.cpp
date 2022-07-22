#include "Entity.h"

void::Entity::initEntities()
{
	this->player.initPlayer();
}

void::Entity::drawGround(sf::RenderWindow* window)
{
	for (int i = 0; i < player.ground.size(); i++)
	{
		this->player.ground[i].draw(window);
	}
}

void::Entity::updateEntities()
{
	this->player.updatePlayer();
}

void::Entity::renderEntities(sf::RenderWindow* window)
{
	this->player.renderPlayer(window);
	this->drawGround(window);
}