#pragma once

#include "Collision.cpp"
class Player : public CollisionAndGround
{
private:
	unsigned short speed = 6;
	//Mov the player
	void movPlayer();

public:
	//Init the Player
	void initPlayer();

	//Update the player
	void updatePlayer();
	//Render the player on screen
	void renderPlayer(sf::RenderWindow* window);
};