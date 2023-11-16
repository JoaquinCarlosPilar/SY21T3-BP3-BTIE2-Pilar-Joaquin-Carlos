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
	// This loads the textures of the game
	texture = loadTexture("gfx/enemy.png");

	// This initializes values to avoide garbage values
	directionX = -1;
	directionY = 1;

	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60;
	currentReloadTime = 0;

	// This times the randomization of direction change 
	directionChangeTime = (rand() % 300) + 120;
	currentDirectionChangeTime = 0;

	// This queries the texture to set the width & height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// This calls and loads the laser sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");

	// This adjusts the volume of the laser projectiles 
	sound->volume = 25;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Enemy::update()
{

	// This moves the enemy
	x += directionX * speed;
	y += directionY * speed;

	// This switches the direcion of the enemy every x seconds
	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		// this flips the direction
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

		// This decrements the enemy's reload timer
		if (currentReloadTime > 0)
			currentReloadTime--;

		if (currentReloadTime == 0)
		{
			float dx = -1; 
			float dy = 0;

			calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

			SoundManager::playSound(sound);
			Bullet* bullet = new Bullet(x - 65 + width, y - 5 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
			bullets.push_back(bullet);

			// This adds and calls a bullet to the scene
			getScene()->addGameObject(bullet);

			// This resets the enemy's reload timer 
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