#include "Bullet.h"
#include "AltBullet.h"
#include "AltBullet2.h"

/*--------------------------------------------------------------------------------------------------------------------*/

Bullet::Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Bullet::start()
{
	// This initializes values to remove garbage values
	width = 0;
	height = 0;

	// This determines which texture to load for the game
	if (side == Side::PLAYER_SIDE)
	{
		texture = loadTexture("gfx/playerBullet.png");
	}

	else if (side == Side::ENEMY_SIDE)
	{
		texture = loadTexture("gfx/alienBullet.png");
	}

	//This sets the width and height properties of the bullet
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Bullet::update()
{
	// This moves the bullets
	// X axis
	x += directionX * speed;

	// Y axis
	y += directionY * speed;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Bullet::draw()
{
	blit(texture, x, y);
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Bullet::getPositionX()
{
	return x;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Bullet::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Bullet::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Bullet::getHeight()
{
	return height;
}

/*--------------------------------------------------------------------------------------------------------------------*/

Side Bullet::getSide()
{
	return side;
}