#include "main.h"

/*--------------------------------------------------------------------------------------------------------------------*/

static void capFrameRate(long* then, float* remainder);

int main(int argc, char* argv[])
{
	srand(time(NULL));
	long then;
	float remainder;

	// Allocate memory for the App struct
	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	// Initialize SDL and open a window
	initSDL();

	// On application exit, call cleanup function
	atexit(cleanup);
	then = SDL_GetTicks();
	remainder = 0;

	// Initialize GameScene or any first scene you want here
	GameScene* scene = new GameScene();

	// Framework code
	// Pass in your initialized variable here
	Scene::setActiveScene(scene);

	// Main game loop
	while (true)
	{
		prepareScene();
		doInput();

		Scene::getActiveScene()->update();
		Scene::getActiveScene()->draw();

		presentScene();

		capFrameRate(&then, &remainder);
	}

	// Delete your instantiated scene here
	delete scene;

	return 0;
}

/*--------------------------------------------------------------------------------------------------------------------*/

static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}