#include "Bullet.h"

/*--------------------------------------------------------------------------------------------------------------------*/

Bullet::Bullet(float positionX, float positionY, float directionX, float directionY, float speed)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Bullet::start()
{
	// This initializes values to remove garbage values
	width = 0;
	height = 0;
	texture = loadTexture("gfx/playerBullet.png");

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

float Bullet::getPostitionX()
{
	return x;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float Bullet::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float Bullet::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

float Bullet::getHeight()
{
	return height;
}