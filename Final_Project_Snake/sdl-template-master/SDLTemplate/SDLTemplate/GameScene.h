#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Grid.h"
#include "Snake.h"
#include "Pickup.h"
#include "util.h"
#include "text.h"
#include "SoundManager.h"

/*--------------------------------------------------------------------------------------*/

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

private:
	Grid* grid;
	Mix_Chunk* sfx;
	Snake* snake;
	Pickup* pickup;

	void spawnPickup();
	void snakePickup();

	int timer;
	int currentTimer;
	int points;
};