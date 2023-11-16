#include "AltBullet.h"
#include "AltBullet2.h"
#include "Bullet.h"

/*--------------------------------------------------------------------------------------------------------------------*/

AltBullet::AltBullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void AltBullet::start()
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

void AltBullet::update()
{
	// This moves the bullets
	// X axis
	x += directionX * speed;

	// Y axis
	y += directionY * speed;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void AltBullet::draw()
{
	blit(texture, x, y);
}

/*--------------------------------------------------------------------------------------------------------------------*/

int AltBullet::getPositionX()
{
	return x;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int AltBullet::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int AltBullet::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int AltBullet::getHeight()
{
	return height;
}

/*--------------------------------------------------------------------------------------------------------------------*/

Side AltBullet::getSide()
{
	return side;
}