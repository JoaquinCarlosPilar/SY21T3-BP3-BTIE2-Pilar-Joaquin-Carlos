#include "Enemy.h"
#include "Scene.h"

/*--------------------------------------------------------------------------------------------------------------------*/

Enemy::Enemy()
{

}

/*--------------------------------------------------------------------------------------------------------------------*/

Enemy::~Enemy()
{

}

/*--------------------------------------------------------------------------------------------------------------------*/

void Enemy::start()
{
	// Load texture
	texture = loadTexture("gfx/Alternate_Enemy.png");

	// Initialize variables
	directionX = 0;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60; // reload time of 60 frames
	currentReloadTime = 0;
	directionChangeTime = (rand() % 60) + 180; // Direction change time of 3-8 seconds
	currentDirectionChangeTime = 0;

	// Query texture to set width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
		directionY = -directionY;
	currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 26, y - 2 + height / 2, dx, dy, 7, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	// Memory manage our bullets. When they go off screen, delete.
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break;
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Enemy::draw()
{
	blit(texture, x, y);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Enemy::getPositionX()
{
	return x;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Enemy::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Enemy::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Enemy::getHeight()
{
	return height;
}