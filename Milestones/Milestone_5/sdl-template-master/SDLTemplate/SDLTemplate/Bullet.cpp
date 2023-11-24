#include "Bullet.h"

/*--------------------------------------------------------------------------------------------------------------------*/

Bullet::Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->backwardspeed = speed;
	this->downspeed = speed;
	this->forwardspeed = speed;
	this->upspeed = speed;
	this->bulletspeed = speed;
	this->side = side;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Bullet::start()
{
	width = 0;
	height = 0;

	if (side == Side::PLAYER_SIDE)
	{
		texture = loadTexture("gfx/playerBullet.png");
	}
	else
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
	x += directionX * bulletspeed;

	// Y axis
	y += directionY * bulletspeed;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Bullet::draw()
{
	blitRotate(texture, x, y, -90);
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