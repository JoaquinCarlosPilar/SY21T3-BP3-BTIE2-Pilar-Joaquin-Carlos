#include "GameScene.h"
#include "Bullet.h"
#include "Enemy.h"

/*--------------------------------------------------------------------------------------------------------------------*/

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

}

/*--------------------------------------------------------------------------------------------------------------------*/

GameScene::~GameScene()
{
	delete player;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::start()
{
	Scene::start();

	// This is the time for the enemies to spawn
	currentSpawnTimer = 180;
	spawnTime = 60;

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::draw()
{
	Scene::draw();
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::update()
{
	Scene::update();

	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{

		for (int i = 0; i < 3; i++)
		{
			spawn();
			currentSpawnTimer = spawnTime;
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

// This is the spawn function of the enemies

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1400, 400 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
}