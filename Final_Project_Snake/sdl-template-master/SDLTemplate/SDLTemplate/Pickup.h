#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

/*--------------------------------------------------------------------------------------*/

class Pickup : public GameObject
{
public:
	Pickup();
	~Pickup();
	void start();
	void draw();
	void update();

	void setPosition(int x, int y);

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture;
	int posX;
	int posY;
	int width;
	int height;
};