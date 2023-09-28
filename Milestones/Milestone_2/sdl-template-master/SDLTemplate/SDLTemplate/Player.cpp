#include "Player.h"
#include "Scene.h"
#include "Bullet.h"

/*--------------------------------------------------------------------------------------------------------------------*/

Player::~Player()
{

	// This delete all bullets when the player dies
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();

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

	// This decrements the player's reload timer
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
		bullet->start();

		// This resets the player's reload timer 
		currentReloadTime = reloadTime;
	}

	// G keybind
	// This is the alternative shoot button
	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 60 + width, y - 32.5 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);

		// This adds and calls a bullet to the scene
		getScene()->addGameObject(bullet);
		bullet->start();

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

}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::draw()
{
	blit(texture, x, y);
}