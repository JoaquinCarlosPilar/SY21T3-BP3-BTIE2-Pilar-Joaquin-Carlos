#include "Pickup.h"

/*--------------------------------------------------------------------------------------*/

Pickup::Pickup()
{

}

/*--------------------------------------------------------------------------------------*/

Pickup::~Pickup()
{

}
 
/*--------------------------------------------------------------------------------------*/

void Pickup::start()
{
	texture = loadTexture("gfx/orange_pickup.png");
	posX = rand() % 20 * 32;
	posY = rand() % 20 * 32;

	width = 32;
	height = 32;
}


/*--------------------------------------------------------------------------------------*/
void Pickup::draw()
{
	blit(texture, posX, posY);
}

/*--------------------------------------------------------------------------------------*/

void Pickup::update()
{

}


/*--------------------------------------------------------------------------------------*/
void Pickup::setPosition(int x, int y)
{
	x = posX;
	y = posY;
}

/*--------------------------------------------------------------------------------------*/

int Pickup::getPosX()
{
	return posX;
}

/*--------------------------------------------------------------------------------------*/

int Pickup::getPosY()
{
	return posY;
}

/*--------------------------------------------------------------------------------------*/

int Pickup::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------*/

int Pickup::getHeight()
{
	return height;
}