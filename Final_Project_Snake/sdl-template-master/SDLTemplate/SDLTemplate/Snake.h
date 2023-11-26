#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"
#include "util.h"
#include "text.h"
#include <vector>
#include "SoundManager.h"

/*--------------------------------------------------------------------------------------*/

class Snake : public GameObject
{
public:
	Snake();
	~Snake();
	void start();
	void draw();
	void update();

	int getNode();
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

	void checkEdges();
	void addLength();
	void snakeDeath();

	bool getIsAlive();

private:
	SDL_Texture* texture;
	Mix_Chunk* sfx;

	std::vector<int> posX;
	std::vector<int> posY;

	int width;
	int height;
	int directionX;
	int directionY;

	float timer;
	float currentTimer;

	bool isAlive;
};