#include "Player.h"
#include "Scene.h"
#include "Bullet.h"
#include "AltBullet.h"
#include "AltBullet2.h"

/*--------------------------------------------------------------------------------------------------------------------*/

Player::~Player()
{

	// This delete all bullets when the player dies (Bullet)
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();

	// (AltBullet)
	for (int i = 0; i < altbullets.size(); i++)
	{
		delete altbullets[i];
	}
	altbullets.clear();

	// (AltBullet2)
	for (int i = 0; i < altbullets2.size(); i++)
	{
		delete altbullets2[i];
	}
	altbullets2.clear();

}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::start()
{

	// This loads the textures of the game
	texture = loadTexture("gfx/player.png");

	// This initializes values to avoide garbage values
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 5; 

	reloadTime = 12;
	currentReloadTime = 0;

	AltReloadTime = 21;
	AltCurrentReloadTime = 0;

	AltReloadTime2 = 21;
	AltCurrentReloadTime2 = 0;

	// This queries the texture to set the width & height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// This calls and loads the laser sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");

}

/*--------------------------------------------------------------------------------------------------------------------*/

// This moves the player's spaceship

void Player::update()
{
	// W keybind
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}

	// A keybind
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	// S keybind
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	// D keybind
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

	/*--------------------------------------------------------------------------------------------------------------------*/

	// This decrements the player's reload timer (Bullet)
	if (currentReloadTime > 0)
		currentReloadTime--;

	// F keybind
	// This is the main shoot button
	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 10 + width, y - 5 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);

		// This adds and calls a bullet to the scene
		getScene()->addGameObject(bullet);

		// This resets the player's reload timer 
		currentReloadTime = reloadTime;
	}

	// This delete bullets that are off the game screen
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPostitionX() > SCREEN_WIDTH)
		{

			// This caches the variable so we can delete it later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;

		}
	}

	/*--------------------------------------------------------------------------------------------------------------------*/

	// This decrements the player's reload timer (AltBullet)
	if (AltCurrentReloadTime > 0)
		AltCurrentReloadTime--;

	// G keybind
	// This is the alternative shoot button
	if (app.keyboard[SDL_SCANCODE_G] && AltCurrentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		AltBullet* altbullet = new AltBullet(x - 60 + width, y - 31 + height / 2, 1, 0, 10);
		altbullets.push_back(altbullet);

		// This adds and calls a bullet to the scene
		getScene()->addGameObject(altbullet);
		altbullet->start();

		// This resets the player's reload timer 
		AltCurrentReloadTime = AltReloadTime;
	}

	// This delete bullets that are off the game screen
	for (int i = 0; i < altbullets.size(); i++)
	{
		if (altbullets[i]->getPostitionX() > SCREEN_WIDTH)
		{

			// This caches the variable so we can delete it later
			AltBullet* altbulletToErase = altbullets[i];
			altbullets.erase(altbullets.begin() + i);
			delete altbulletToErase;

			break;

		}
	}

/*--------------------------------------------------------------------------------------------------------------------*/

	// This decrements the player's reload timer (AltBullet2)
	if (AltCurrentReloadTime2 > 0)
		AltCurrentReloadTime2--;

	// G keybind
	// This is the alternative shoot button 2
	if (app.keyboard[SDL_SCANCODE_G] && AltCurrentReloadTime2 == 0)
	{
		SoundManager::playSound(sound);
		AltBullet2* altbullet2 = new AltBullet2(x - 60 + width, y + 23 + height / 2, 1, 0, 10);
		altbullets2.push_back(altbullet2);

		// This adds and calls a bullet to the scene
		getScene()->addGameObject(altbullet2);
		altbullet2->start();

		// This resets the player's reload timer 
		AltCurrentReloadTime2 = AltReloadTime2;
	}

	// This delete bullets that are off the game screen
	for (int i = 0; i < altbullets2.size(); i++)
	{
		if (altbullets2[i]->getPostitionX() > SCREEN_WIDTH)
		{

			// This caches the variable so we can delete it later
			AltBullet2* altbulletToErase2 = altbullets2[i];
			altbullets2.erase(altbullets2.begin() + i);
			delete altbulletToErase2;

			break;

		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::draw()
{
	blit(texture, x, y);
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}
