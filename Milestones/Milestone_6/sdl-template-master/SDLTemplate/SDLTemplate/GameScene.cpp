#include "GameScene.h"
#include "Scene.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

/*--------------------------------------------------------------------------------------------------------------------*/

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player;
	this->addGameObject(player);

	int bossSpawn = 0;
	int bossCounter = 0;
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
	powerUpSound = SoundManager::loadSound("sound/powerUp.ogg");
	initFonts();

	currentSpawnTimer = 300;

	// Spawn time of 5 seconds
	spawnTime = 300; 

	for (int i = 0; i < 5; i++)
	{
		spawn();
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
	doSpawnLogic();
	doCollisionLogic();
	doPowerupCollision();
	dobossCollision();
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::doSpawnLogic()
{
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (bossCounter <= 9 && currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 5; i++)
		{
			spawn();
		}
		spawnPowerup();
		currentSpawnTimer = spawnTime;
	}
	else if (currentSpawnTimer == 0 && bossCounter > 9 && bossSpawn == 0)
	{
		bossSpawns();
		currentSpawnTimer = 0;
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::doCollisionLogic()
{
	// Check for collision
	for (int i = 0; i < objects.size(); i++)
	{
		// Cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);
		
		if (bullet != NULL)
		{
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
			// If the bullet is from the player side, check against ALL enemies
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
						despawnEnemy(currentEnemy);
						// Increment points
						points++;
						bossCounter++;
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		Enemy* currentEnemy = spawnedEnemies[i];
		if (currentEnemy->getPositionY() > SCREEN_HEIGHT - 20)
		{
			despawnEnemy(currentEnemy);
			break;
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::doPowerupCollision()
{
	for (int i = 0; i < objects.size(); i++)
	{
		Powerup* powerup = dynamic_cast<Powerup*>(objects[i]);
		if (powerup != NULL)
		{
			int collision = checkCollision(
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
				powerup->getPositionX(), powerup->getPositionY(), powerup->getWidth(), powerup->getHeight()
			);
			for (int i = 0; i < spawnedPowerups.size(); i++)
			{
				Powerup* currentPowerup = spawnedPowerups[i];
				if (collision == 1)
				{
					SoundManager::playSound(powerUpSound);
					player->getAddBullet(1);
					despawnPowerup(currentPowerup);
					break;
				}
			}
		}
	}
	for (int i = 0; i < spawnedPowerups.size(); i++)
	{
		Powerup* currentPowerup = spawnedPowerups[i];
		if (currentPowerup->getPositionY() > SCREEN_HEIGHT - 20)
		{
			despawnPowerup(currentPowerup);
			break;
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(100 + rand() % 400, -200 + rand() % 200);
	spawnedEnemies.push_back(enemy);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = 0;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		// If the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	// If any match is found
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::spawnPowerup()
{
	Powerup* powerup = new Powerup();
	this->addGameObject(powerup);

	powerup->setPosition(100 + rand() % 400, -200 + rand() % 200);
	spawnedPowerups.push_back(powerup);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::despawnPowerup(Powerup* powerup)
{
	int index = 0;
	for (int i = 0; i < spawnedPowerups.size(); i++)
	{
		if (powerup == spawnedPowerups[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		spawnedPowerups.erase(spawnedPowerups.begin() + index);
		delete powerup;
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::bossSpawns()
{
	Boss* boss = new Boss();
	this->addGameObject(boss);

	boss->setPosition(200, 1);
	spawnedBoss.push_back(boss);
	bossSpawn++;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::dobossCollision()
{
	for (int i = 0; i < objects.size(); i++)
	{
		// Cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);


		if (bullet != NULL)
		{
		
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

			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedBoss.size(); i++)
				{
					Boss* currentBoss = spawnedBoss[i];

					int collision = checkCollision(
						currentBoss->getPositionX(), currentBoss->getPositionY(), currentBoss->getWidth(), currentBoss->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if ((currentBoss->getHP() > 0) && (collision == 1))
					{
						currentBoss->getDamage(1);
						break;
					}
					else if (currentBoss->getHP() <= 0 && collision == 1)
					{
						bossCounter = 0;
						despawnBoss(currentBoss);
						points += 5;
						break;
					}
				}
			}
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::despawnBoss(Boss* boss)
{
	int index = 0;
	bossSpawn = 0;
	currentSpawnTimer = spawnTime;
	for (int i = 0; i < spawnedBoss.size(); i++)
	{
		if (boss == spawnedBoss[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		spawnedBoss.erase(spawnedBoss.begin() + index);
		delete boss;
	}
}