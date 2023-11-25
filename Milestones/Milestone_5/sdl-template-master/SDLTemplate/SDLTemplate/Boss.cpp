#include "Boss.h"
#include "Scene.h"

/*--------------------------------------------------------------------------------------------------------------------*/

Boss::Boss()
{

}

/*--------------------------------------------------------------------------------------------------------------------*/

Boss::~Boss()
{

}

/*--------------------------------------------------------------------------------------------------------------------*/

void Boss::start()
{
	// Load texture
	texture = loadTexture("gfx/Alternate_Boss.png");

	// Initialize variables
	hp = 1000;
	directionX = -1;
	directionY = 0;
	width = 0;
	height = 0;
	speed = 2;

	reloadTime = 20; 
	directionChangeTime = (rand() % 50) + 50; 
	currentDirectionChangeTime = 0;
	bulletSpawned = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 50;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Boss::update()
{
	x += directionX * speed;

	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
	}

	if (currentDirectionChangeTime == 0)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
		bulletSpawned = 0;
	}

	if (currentReloadTime == 0 && bulletSpawned == 0)
	{
		bulletSpawned = 1;
		float dx = 0;
		float dy = 1;

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 3.5 + width, y - 2 + height / 2, dx, dy, 5, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		Bullet* bullet1 = new Bullet(x + 30 + width, y - 2 + height / 2, dx, dy, 5, Side::ENEMY_SIDE);
		bullets.push_back(bullet1);
		getScene()->addGameObject(bullet1);

		Bullet* bullet2 = new Bullet(x - 300 + width, y - 2 + height / 2, dx, dy, 5, Side::ENEMY_SIDE);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);

		Bullet* bullet3 = new Bullet(x - 337.5 + width, y - 2 + height / 2, dx, dy, 5, Side::ENEMY_SIDE);
		bullets.push_back(bullet3);
		getScene()->addGameObject(bullet3);

		Bullet* bullet4 = new Bullet(x - 70 + width, y - 2 + height / 2, dx, dy, 5, Side::ENEMY_SIDE);
		bullets.push_back(bullet4);
		getScene()->addGameObject(bullet4);

		Bullet* bullet5 = new Bullet(x - 200 + width, y - 2 + height / 2, dx, dy, 5, Side::ENEMY_SIDE);
		bullets.push_back(bullet5);
		getScene()->addGameObject(bullet5);
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

void Boss::draw()
{
	blit(texture, x, y);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Boss::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Boss::getHP()
{
	return hp;
}

/*--------------------------------------------------------------------------------------------------------------------*/
int Boss::getDamage(int damage)
{
	hp -= damage;
	return hp;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Boss::getPositionX()
{
	return x;
}

int Boss::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Boss::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Boss::getHeight()
{
	return height;
}