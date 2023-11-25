#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Player.h"
#include <vector>
#include "util.h"

/*--------------------------------------------------------------------------------------------------------------------*/

class Powerup : public GameObject
{
public:
	Powerup();
	~Powerup();

	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

	void setPosition(int xPos, int yPos);

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;

	int x;
	int y;
	int xPos;
	int yPos;
	int width;
	int height;
	int speed;

	float directionX;
	float directionY;
};