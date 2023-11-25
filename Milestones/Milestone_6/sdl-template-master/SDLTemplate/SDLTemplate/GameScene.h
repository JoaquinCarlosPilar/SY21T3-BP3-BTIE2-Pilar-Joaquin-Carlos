#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "Powerup.h"
#include "Boss.h"
#include "SoundManager.h"

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
	Powerup* powerup;
	Boss* boss;

	// Enemy spawning logic
	float spawnTime;
	float currentSpawnTimer;

	Mix_Chunk* powerUpSound;
	std::vector<Enemy*> spawnedEnemies;
	std::vector<Powerup*> spawnedPowerups;
	std::vector<Boss*> spawnedBoss;

	void doSpawnLogic();
	void doCollisionLogic();
	void doPowerupCollision();
	void spawn();
	void despawnEnemy(Enemy* enemy);
	void spawnPowerup();
	void despawnPowerup(Powerup* powerup);
	void bossSpawns();
	void dobossCollision();
	void despawnBoss(Boss* boss);

	int bossSpawn;
	int bossCounter;
	int points;
};