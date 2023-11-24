#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include <vector>
#include "text.h"
#include "draw.h"
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

	//FOR SDL 
	SDL_Texture* texture;
	Mix_Chunk* sound;

	//EQUALS TO NEW CLASS
	Player* player;
	PowerUp* powerup;

	// Powerup Spawning Logic
	float spawnTimeUp;
	float currentUpSpawnTimer;

	std::vector<PowerUp* > spawnedUps;

	// Enemy spawning logic
	float spawnTime;
	float currentSpawnTimer;

	std::vector<Enemy* > spawnedEnemies;

	int x;
	int y;
	int width;
	int height;

	void spawn();
	void spawnUp();
	void despawnEnemy(Enemy* enemy);
	void doCheckCollision();
	void doCheckSpawn();

	int points;
};