#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "AltBullet.h"
#include "AltBullet2.h"
#include "Enemy.h"
#include <vector>
#include "text.h"

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
	Enemy* enemy;

	// This is the enemy spawning logic
	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;

	// This function spawns and despawns the characters
	void doSpawnLogic();
	void doCollisionLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);

	int points;
};