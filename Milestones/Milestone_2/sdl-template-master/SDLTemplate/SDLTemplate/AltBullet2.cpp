#include "AltBullet2.h"

/*--------------------------------------------------------------------------------------------------------------------*/

AltBullet2::AltBullet2(float positionX, float positionY, float directionX, float directionY, float speed)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void AltBullet2::start()
{
	// This initializes values to remove garbage values
	width = 0;
	height = 0;
	texture = loadTexture("gfx/playerBullet.png");

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

float AltBullet2::getPostitionX()
{
	return x;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float AltBullet2::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float AltBullet2::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float AltBullet2::getHeight()
{
	return height;
}