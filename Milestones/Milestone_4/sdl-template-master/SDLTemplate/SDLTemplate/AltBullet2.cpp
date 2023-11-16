#include "Bullet.h"
#include "AltBullet.h"
#include "AltBullet2.h"

/*--------------------------------------------------------------------------------------------------------------------*/

AltBullet2::AltBullet2(float positionX, float positionY, float directionX, float directionY, float speed, Side side)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void AltBullet2::start()
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

void AltBullet2::update()
{
	// This moves the bullets
	// X axis
	x += directionX * speed;

	// Y axis
	y += directionY * speed;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void AltBullet2::draw()
{
	blit(texture, x, y);
}

/*--------------------------------------------------------------------------------------------------------------------*/

int AltBullet2::getPositionX()
{
	return x;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int AltBullet2::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int AltBullet2::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int AltBullet2::getHeight()
{
	return height;
}

/*--------------------------------------------------------------------------------------------------------------------*/

Side AltBullet2::getSide()
{
	return side;
}