#include "GameScene.h"
#include "Scene.h"
#include "Bullet.h"
#include "AltBullet.h"
#include "AltBullet2.h"
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

	initFonts();

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

	drawText(115, 15, 173, 216, 230, TEXT_CENTER, "POINTS: %03d", points);

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
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::doSpawnLogic()
{
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
}

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::doCollisionLogic()
{
	// This checks the collision
	for (int i = 0; i < objects.size(); i++)
	{

		// This casts to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);


		// This checks if the cast was successful 
		if (bullet != NULL)
		{

			// This checks if the bullet is from the ENEMY side
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision
				(

					player->getPositionX(),
					player->getPositionY(),
					player->getWidth(),
					player->getHeight(),
					bullet->getPositionX(),
					bullet->getPositionY(),
					bullet->getWidth(),
					bullet->getHeight()

				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}

			// This checks if the bullet is from the PLAYER side
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision
					(

						currentEnemy->getPositionX(),
						currentEnemy->getPositionY(),
						currentEnemy->getWidth(),
						currentEnemy->getHeight(),
						bullet->getPositionX(),
						bullet->getPositionY(),
						bullet->getWidth(),
						bullet->getHeight()

					);

					if (collision == 1)
					{

						// This increments the player's points
						points++;

						// This despawns one enemy at a time
						despawnEnemy(currentEnemy);
						break;
					}
				}
			}
		}
	}

	/*--------------------------------------------------------------------------------------------------------------------*/

	// This checks the collision (AltBullet)
	for (int i = 0; i < objects.size(); i++)
	{

		// This casts to bullet (AltBullet)
		AltBullet* altbullet = dynamic_cast<AltBullet*>(objects[i]);

		// This checks if the cast was successful 
		if (altbullet != NULL)
		{

			// This checks if the bullet is from the ENEMY side
			if (altbullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision
				(

					player->getPositionX(),
					player->getPositionY(),
					player->getWidth(),
					player->getHeight(),
					altbullet->getPositionX(),
					altbullet->getPositionY(),
					altbullet->getWidth(),
					altbullet->getHeight()

				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}

			// This checks if the bullet is from the PLAYER side
			else if (altbullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision
					(

						currentEnemy->getPositionX(),
						currentEnemy->getPositionY(),
						currentEnemy->getWidth(),
						currentEnemy->getHeight(),
						altbullet->getPositionX(),
						altbullet->getPositionY(),
						altbullet->getWidth(),
						altbullet->getHeight()

					);

					if (collision == 1)
					{

						// This increments the player's points
						points++;

						// This despawns one enemy at a time
						despawnEnemy(currentEnemy);
						break;
					}
				}
			}
		}
	}

	/*--------------------------------------------------------------------------------------------------------------------*/

	// This checks the collision (AltBullet2)
	for (int i = 0; i < objects.size(); i++)
	{

		// This casts to bullet (AltBullet2)
		AltBullet2* altbullet2 = dynamic_cast<AltBullet2*>(objects[i]);

		// This checks if the cast was successful 
		if (altbullet2 != NULL)
		{

			// This checks if the bullet is from the ENEMY side
			if (altbullet2->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision
				(

					player->getPositionX(),
					player->getPositionY(),
					player->getWidth(),
					player->getHeight(),
					altbullet2->getPositionX(),
					altbullet2->getPositionY(),
					altbullet2->getWidth(),
					altbullet2->getHeight()

				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}

			// This checks if the bullet is from the PLAYER side
			else if (altbullet2->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision
					(

						currentEnemy->getPositionX(),
						currentEnemy->getPositionY(),
						currentEnemy->getWidth(),
						currentEnemy->getHeight(),
						altbullet2->getPositionX(),
						altbullet2->getPositionY(),
						altbullet2->getWidth(),
						altbullet2->getHeight()

					);

					if (collision == 1)
					{

						// This increments the player's points
						points++;

						// This despawns one enemy at a time
						despawnEnemy(currentEnemy);
						break;
					}
				}
			}
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

/*--------------------------------------------------------------------------------------------------------------------*/

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{

		// This is if the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	// This is if any match has been found
	if (index != 1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}