#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

/*--------------------------------------------------------------------------------------------------------------------*/

class Boss :
	public GameObject
{
public:
	Boss();
	~Boss();

	void start();
	void update();
	void draw();
	void setPosition(int xPos, int yPos);

	int getHP();
	int getDamage(int damage);
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	Player* playerTarget;

	int x;
	int y;
	int hp;
	int damage;

	float directionX;
	float directionY;

	int width;
	int height;
	int speed;
	int bulletSpawned;

	float reloadTime;
	float currentReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;

	std::vector<Bullet*> bullets;
};