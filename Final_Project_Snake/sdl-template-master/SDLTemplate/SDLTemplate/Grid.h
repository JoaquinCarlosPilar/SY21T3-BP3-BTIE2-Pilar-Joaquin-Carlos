#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include <vector>

/*--------------------------------------------------------------------------------------*/

class Grid : public GameObject
{
public:
	Grid();
	~Grid();
	void start();
	void draw();
	void update();

	int getGridWidth();
	int getGridHeight();
	int getGridSize();

private:
	SDL_Texture* texture;
	int width;
	int height;
	int size;
};