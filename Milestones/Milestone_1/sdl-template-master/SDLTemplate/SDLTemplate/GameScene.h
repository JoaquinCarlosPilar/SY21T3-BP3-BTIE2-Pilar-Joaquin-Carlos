#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"

/*--------------------------------------------------------------------------------------------------------------------*/

class GameScene : public Scene
{

public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

private:
	Player* player;
};