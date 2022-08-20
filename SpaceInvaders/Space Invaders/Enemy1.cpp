#pragma once

#include "Entity.cpp"

class Enemy1 : public Entity
{
private:
	std::string name = "EN1";

	void mov(const float speed)
	{
		if (life > 2)
		{
			if (right) position.x += speed;
			else position.x -= speed;
		}
		sprite.setPosition(position);
	}
	void animation(sf::Texture anim[2])
	{
		sprite.setTexture(anim[actualFrame]);
		if (timer < limitimer)
			timer++;
		else
		{
			if (actualFrame < 1) actualFrame++;
			else actualFrame = 0;
			timer = 0;
		}
	}
	virtual void shoot(sf::Texture& txtr, std::vector<TiroEn> &tiros)
	{
		if (life > 2)
		{
			tiros.push_back(TiroEn());
			tiros[tiros.size() - 1].init(txtr, { 0,4 }, { position.x + tam.x / 2, position.y + tam.y });
		}
	}
public:
	virtual void update(sf::Texture texture[2], const float speed)
	{
		mov(speed);
		animation(texture);
		if (life <= 2) this->position.y += 2;
	}
	virtual void render(sf::RenderWindow* i_window)
	{
		i_window->draw(sprite);
	}
	virtual void init(sf::Vector2f position, sf::Texture texture[2])
	{
		this->position = position;
		sprite.setTexture(texture[0]);
		sprite.setScale({ 3,3 });
		tam.x = sprite.getLocalBounds().width * 3;
		tam.y = sprite.getLocalBounds().height * 3;
	}
	virtual void walkOneTile()
	{
		if (life > 2)
		{
			if (right)
			{
				this->position.y += 21;
				this->position.x += 7;
			}
			else
			{
				this->position.y += 21;
				this->position.x -= 7;
			}
		}
	}
	virtual void setRight(bool right) { this->right = right; }
	virtual sf::FloatRect getBounds() { return sf::FloatRect(position.x, position.y, tam.x, tam.y); }
	virtual sf::Vector2f getPosition() { return position; }
	virtual std::string getName() { return name; }
};