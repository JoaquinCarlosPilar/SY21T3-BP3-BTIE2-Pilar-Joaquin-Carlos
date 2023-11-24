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
	// Load Texture
	texture = loadTexture("gfx/player.png");

	// Initialize to avoid garbage values
	x = 350;
	y = 650;
	width = 0;
	height = 0;
	upspeed = 6;
	downspeed = 6;
	forwardspeed = 6;
	backwardspeed = 6;
	bulletspeed = 12;
	reloadTime = 12;
	currentReloadTime = 0;
	isAlive = true;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::update()
{
	// Memory manage our bullets. When they go off screen, delete them 
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT) 
		{
			// This caches the variable so we can delete it later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
		}
	}
	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= upspeed;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += downspeed;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= backwardspeed;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += forwardspeed;
	}

	// LSHIFT keybind
	// This increases the player's speed to 10
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		forwardspeed = 10;
		backwardspeed = 10;
		upspeed = 10;
		downspeed = 10;
	}

	// BACKSPACE keybind
	// This reverts the player's speed to 5
	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		forwardspeed = 5;
		backwardspeed = 5;
		upspeed = 5;
		downspeed = 5;
	}

	// Decrement the player's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 11, y - 1.5 + height / 2, 0, -2, 7, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

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

bool Player::getIsAlive()
{
	return isAlive;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::doDeath()
{
	isAlive = false;
}