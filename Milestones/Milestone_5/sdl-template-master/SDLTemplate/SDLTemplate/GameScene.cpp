#include "GameScene.h"
#include "Scene.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

/*--------------------------------------------------------------------------------------------------------------------*/

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
	points = 0;

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
	// Initialize any scene logic here

	initFonts();
	currentSpawnTimer = 180;
	spawnTime = 150; 

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}

	// This spawns the powerup
	currentUpSpawnTimer = 600;
	spawnTimeUp = 600; 

	for (int i = 0; i < 1; i++)
	{
		spawnUp();
	}

}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::draw()

{
	Scene::draw();
	drawText(110, 20, 173, 216, 230, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, 350, 238, 75, 43, TEXT_CENTER, "YOU DIED");
	}

}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::update()
{
	Scene::update();
	doCheckSpawn();
	doCheckCollision();
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::spawn()
{
	//ENEMY SPAWN
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(50, -500 + (rand() % 300));
	spawnedEnemies.push_back(enemy);

}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::spawnUp()
{

	// SPAWN LOGIC FOR POWERUPS ONLY
	PowerUp* powerup = new PowerUp();
	this->addGameObject(powerup);

	powerup->setPositionUp(-5, -1500 + (rand() % 300));
	spawnedUps.push_back(powerup);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		// If the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}
	// if any match is found
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
		texture = loadTexture("gfx/explosion.png");
		blit(texture, x, y);
		SoundManager::playSound(sound);
	}


}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::doCheckCollision()
{
	// Checks for Collision
	for (int i = 0; i < objects.size(); i++)
	{
		//Case to bullet 
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);
		// Check if the cast was successful (i.e objects [i] is a Bullet)
		if (bullet != NULL)
		{
			// If the bullet is the enemy side, check against the player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}

			// If the bullet is the player side, check against ALL Enemies
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];
					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						//despawn one at the time (might crash)
						despawnEnemy(currentEnemy);
						//increment points
						points++;
						break;
					}
				}
			}
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/


void GameScene::doCheckSpawn()
{
	// FOR ENEMY SPAWN (3 SPAWN PER WAVE)
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
		}
		currentSpawnTimer = spawnTime;
	}

	// FOR POWER UP SPAWN (ONLY 1 SPAWN)
	if (currentUpSpawnTimer > 0)
		currentUpSpawnTimer--;

	if (currentUpSpawnTimer <= 0)
	{
		for (int i = 0; i < 1; i++)
		{
			spawnUp();
		}
		currentUpSpawnTimer = spawnTimeUp;
	}
}