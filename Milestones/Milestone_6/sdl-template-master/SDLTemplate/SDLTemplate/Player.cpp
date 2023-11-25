#include "Player.h"
#include "GameScene.h"
#include "Scene.h"
#include "Bullet.h"

/*--------------------------------------------------------------------------------------------------------------------*/

Player::~Player()
{
	// Memory manage our bullets. Delete all bullets on player deletion/death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::start()
{
	// Load texture
	texture = loadTexture("gfx/Alternate_Player.png");

	// Initialize variables
	x = 350;
	y = 650;
	width = 0;
	height = 0;
	speed = 5;
	reloadTime = 10; 
	currentReloadTime = 0;
	isAlive = true;

	// Query texture to set width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::update()
{
	// Memory manage our bullets. When they go off screen, delete.
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			// This caches the variable so we can delete it later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break;
		}
	}

	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	// LSHIFT keybind
	// This increases the player's speed to 10
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 10;
	}

	// BACKSPACE keybind
	// This reverts the player's speed to 5
	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 5;
	}


	// Decrement the player's reload time
	if (currentReloadTime > 0)
		currentReloadTime--;

	// Firing Bullet
	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 11, y - 22 + height / 2, 0, -2, 7, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		if (addBullet == 1)
		{
			Bullet* bulletPlus = new Bullet(x + 24, y - 22 + height / 2, 0, -2, 7, Side::PLAYER_SIDE);
			bullets.push_back(bulletPlus);
			getScene()->addGameObject(bulletPlus);
		}

		else if (addBullet >= 2)
		{
			Bullet* bulletPlus = new Bullet(x - 30 + width / 2, y - 40 + height, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bulletPlus);
			getScene()->addGameObject(bulletPlus);
			Bullet* bulletPlus1 = new Bullet(x + 4 + width / 2, y - 40 + height, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bulletPlus1);
			getScene()->addGameObject(bulletPlus1);
		}

		// After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	// Alternate Firing Bullet
	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 11, y - 22 + height / 2, 0, -2, 14, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		if (addBullet == 1)
		{
			Bullet* bulletPlus = new Bullet(x + 44, y - 22 + height / 2, 0, -2, 14, Side::PLAYER_SIDE);
			bullets.push_back(bulletPlus);
			getScene()->addGameObject(bulletPlus);
		}

		else if (addBullet >= 2)
		{
			Bullet* bulletPlus = new Bullet(x - 50 + width / 2, y - 40 + height, 0, -1, 20, Side::PLAYER_SIDE);
			bullets.push_back(bulletPlus);
			getScene()->addGameObject(bulletPlus);
			Bullet* bulletPlus1 = new Bullet(x + 24 + width / 2, y - 40 + height, 0, -1, 20, Side::PLAYER_SIDE);
			bullets.push_back(bulletPlus1);
			getScene()->addGameObject(bulletPlus1);
		}

		// After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::draw()
{
	if (!isAlive) return;
	blitRotate(texture, x, y, -90);
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Player::getPositionX()
{
	return x;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Player::getPositionY()
{
	return y;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Player::getWidth()
{
	return width;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Player::getHeight()
{
	return height;
}

/*--------------------------------------------------------------------------------------------------------------------*/

int Player::getAddBullet(int bulletnum)
{
	addBullet = addBullet + bulletnum;
	return addBullet;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool Player::getIsAlive()
{
	return isAlive;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::doDeath()
{
	isAlive = false;
}