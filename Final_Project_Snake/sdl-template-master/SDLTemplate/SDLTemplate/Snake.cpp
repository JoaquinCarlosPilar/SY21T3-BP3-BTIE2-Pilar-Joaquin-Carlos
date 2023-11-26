#include "Snake.h"

/*--------------------------------------------------------------------------------------*/

Snake::Snake()
{

}

/*--------------------------------------------------------------------------------------*/

Snake::~Snake()
{

}

/*--------------------------------------------------------------------------------------*/

void Snake::start()
{
	texture = loadTexture("gfx/snake_body.png");
	width = 32;
	height = 32;

	directionX = 1;
	directionY = 0;
	timer = 20;
	currentTimer = 20;

	isAlive = true;

	posX.push_back(8 * width);
	posY.push_back(8 * height);

	posX.push_back(9 * width);
	posY.push_back(8 * height);

	posX.push_back(10 * width);
	posY.push_back(8 * height);

	sfx = SoundManager::loadSound("sound/oof_turn.ogg");

}

/*--------------------------------------------------------------------------------------*/

void Snake::draw()
{
	if (!isAlive) return;

	for (int i = 0; i < posX.size(); i++)
	{
		blit(texture, posX[i], posY[i]);
	}
}

/*--------------------------------------------------------------------------------------*/

void Snake::update()
{
	if (!isAlive) return;

	if (currentTimer > 0)
	{
		currentTimer--;
	}

	if (currentTimer <= 0)
	{
		checkEdges();

		for (int i = 0; i < posX.size() - 1; i++)
		{
			int next = i + 1;

			posX[i] = posX[next];
			posY[i] = posY[next];
		}

		posX[getNode()] += directionX * width;
		posY[getNode()] += directionY * height;

		currentTimer = timer;
	}

	//Player Snake controls
	if (app.keyboard[SDL_SCANCODE_W] || app.keyboard[SDL_SCANCODE_UP]) // Move up
	{
		SoundManager::playSound(sfx);
		sfx->volume = 50;
		if (directionY != 1)
		{
			directionX = 0;
			directionY = -1;
		}
	}

	else if (app.keyboard[SDL_SCANCODE_S] || app.keyboard[SDL_SCANCODE_DOWN]) //Move down
	{
		SoundManager::playSound(sfx);
		sfx->volume = 50;
		if (directionY != -1)
		{
			directionX = 0;
			directionY = 1;
		}
	}

	else if (app.keyboard[SDL_SCANCODE_A] || app.keyboard[SDL_SCANCODE_LEFT]) //Move left
	{
		SoundManager::playSound(sfx);
		sfx->volume = 50;
		if (directionX != 1)
		{
			directionX = -1;
			directionY = 0;
		}
	}

	else if (app.keyboard[SDL_SCANCODE_D] || app.keyboard[SDL_SCANCODE_RIGHT]) //Move right
	{
		SoundManager::playSound(sfx);
		sfx->volume = 50;
		if (directionX != -1)
		{
			directionX = 1;
			directionY = 0;
		}
	}
}

/*--------------------------------------------------------------------------------------*/

int Snake::getNode()
{
	return posX.size() - 1;
}

/*--------------------------------------------------------------------------------------*/

int Snake::getPosX()
{
	return posX[posX.size() - 1];
}

/*--------------------------------------------------------------------------------------*/

int Snake::getPosY()
{
	return posY[posY.size() - 1];
}

/*--------------------------------------------------------------------------------------*/

int Snake::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------*/

int Snake::getHeight()
{
	return height;
}

/*--------------------------------------------------------------------------------------*/

void Snake::checkEdges()
{
	if (posX[getNode()] < 0) //If player exceeds left side
	{
		posX[getNode()] = SCREEN_WIDTH;
		directionX = -1;
	}

	if (posX[getNode()] > SCREEN_WIDTH) //If player exceeds right side
	{
		posX[getNode()] = 0;
		directionX = 1;
	}

	if (posY[getNode()] < 0) //If player exceeds top side
	{
		posY[getNode()] = SCREEN_HEIGHT;
		directionY = -1;
	}

	if (posY[getNode()] > SCREEN_HEIGHT) //If player exceeds bottom side
	{
		posY[getNode()] = 0;
		directionY = 1;
	}
}

/*--------------------------------------------------------------------------------------*/

void Snake::addLength()
{
	int index = getNode();

	posX.push_back(posX[index]);
	posY.push_back(posY[index]);

	timer--;
	currentTimer--;
}

/*--------------------------------------------------------------------------------------*/

void Snake::snakeDeath()
{
	for (int i = 0; i < posX.size() - 1; i++)
	{
		int collision = checkCollision(getPosX(), getPosY(), width, height, posX[i], posY[i], width, height);

		if (collision == 1)
		{
			isAlive = false;
			break;
		}
	}
}

/*--------------------------------------------------------------------------------------*/

bool Snake::getIsAlive()
{
	return isAlive;
}