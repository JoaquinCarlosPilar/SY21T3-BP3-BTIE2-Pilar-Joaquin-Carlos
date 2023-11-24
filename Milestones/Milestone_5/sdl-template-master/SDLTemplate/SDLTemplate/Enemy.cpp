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
	// Load Texture
	texture = loadTexture("gfx/enemy.png");
	// Initialize to avoid garbage values

	enemyspeed = 2;
	directionX = -2;
	directionY = 1;
	width = 0;
	height = 0;
	upspeed = 2;
	downspeed = 2;
	forwardspeed = 2;
	backwardspeed = 2;

	bulletspeed = 4;
	reloadTime = 60;

	currentReloadTime = 0;
	directionChangeTime = (rand() % 250) + 60; //Direction Change time of 2.5
	currentDirectionChangeTime = 0;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");

	// This adjusts the volume of the laser projectiles 
	sound->volume = 25;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Enemy::update()
{
	// This moves the enemy
	x += directionX * enemyspeed;
	y += directionY * enemyspeed;


	// This switches the direcion of the enemy every x seconds
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

	// This decrements the enemy's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 11, y - 1.5 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			// This caches the variable so we can delete it later
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
	blitRotate(texture, x, y, -90);
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