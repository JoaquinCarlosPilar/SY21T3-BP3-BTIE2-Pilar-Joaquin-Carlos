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

class PowerUp : public GameObject
{
public:
	PowerUp();
	~PowerUp();

	void start();
	void update();
	void draw();
	void setPositionUp(int xPos, int yPos);


private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;

	float directionX;
	float directionY;

	int width;
	int height;

	int powerupSpeed;
	float currentReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;
};