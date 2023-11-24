#include "PowerUp.h"

/*--------------------------------------------------------------------------------------------------------------------*/

PowerUp::PowerUp()
{

}

/*--------------------------------------------------------------------------------------------------------------------*/

PowerUp::~PowerUp()
{

}

/*--------------------------------------------------------------------------------------------------------------------*/

void PowerUp::start()
{
	// Load Texture
	texture = loadTexture("gfx/points.png");
	// Initialize to avoid garbage values

	powerupSpeed = 1;
	directionX = -4;
	directionY = 4;
	width = 0;
	height = 0;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 100) + 100; //Direction Change time of 2.5
	currentDirectionChangeTime = 0;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);


}

/*--------------------------------------------------------------------------------------------------------------------*/

void PowerUp::update()
{

	x += directionX * powerupSpeed;
	y += directionY * powerupSpeed;

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		-directionY == -directionY;
		directionX = -directionX;

		currentDirectionChangeTime = directionChangeTime;
	}
	else
		- directionY == -directionY;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void PowerUp::draw()
{
	blit(texture, x, y);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void PowerUp::setPositionUp(int xPos, int yPos)

{
	this->x = xPos;
	this->y = yPos;
}