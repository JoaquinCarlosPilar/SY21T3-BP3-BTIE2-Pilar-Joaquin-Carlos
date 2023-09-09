#include "Player.h"

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::start()
{

	// This loades the textures of the game
	texture = loadTexture("gfx/player.png");

	// This initializes values to avoide garbage values
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 5; 

	// This queries the texture to set the width & height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
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

}

/*--------------------------------------------------------------------------------------------------------------------*/

void Player::draw()
{
	blit(texture, x, y);
}