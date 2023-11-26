#include "GameScene.h"

/*--------------------------------------------------------------------------------------*/

GameScene::GameScene()
{
	// Register and add game objects on constructor
}

/*--------------------------------------------------------------------------------------*/

GameScene::~GameScene()
{

}

/*--------------------------------------------------------------------------------------*/

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();
	grid = new Grid();
	this->addGameObject(grid);

	snake = new Snake();
	this->addGameObject(snake);

	timer = 100;
	currentTimer = 100;
	points = 0;

	sfx = SoundManager::loadSound("sound/pop_pickup.ogg");

	spawnPickup();
}

/*--------------------------------------------------------------------------------------*/

void GameScene::draw()
{
	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (snake->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "YOU DIED"); //Game Over Text
	}
}

/*--------------------------------------------------------------------------------------*/

void GameScene::update()
{
	Scene::update();

	snakePickup();
	//snake->snakeDeath();
}

/*--------------------------------------------------------------------------------------*/

void GameScene::spawnPickup()
{
	std::cout << "Pickup spawned" << std::endl;
	pickup = new Pickup;
	this->addGameObject(pickup);
}

/*--------------------------------------------------------------------------------------*/

void GameScene::snakePickup()
{
	int collision = checkCollision(snake->getPosX(), snake->getPosY(), snake->getWidth(), snake->getHeight(), 
								pickup->getPosX(), pickup->getPosY(), pickup->getWidth(), pickup->getHeight());

	if (collision == 1)
	{
		delete pickup;
		spawnPickup();
		snake->addLength();
		points++;

		SoundManager::playSound(sfx);
	}
}