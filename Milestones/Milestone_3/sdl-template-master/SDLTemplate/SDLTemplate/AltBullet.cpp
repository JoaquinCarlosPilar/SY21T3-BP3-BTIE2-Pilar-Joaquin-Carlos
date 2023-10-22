#include "AltBullet.h"

/*--------------------------------------------------------------------------------------------------------------------*/

AltBullet::AltBullet(float positionX, float positionY, float directionX, float directionY, float speed)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void AltBullet::start()
{
	// This initializes values to remove garbage values
	width = 0;
	height = 0;
	texture = loadTexture("gfx/playerBullet.png");

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

float AltBullet::getPostitionX()
{
	return x;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float AltBullet::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float AltBullet::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float AltBullet::getHeight()
{
	return height;
}