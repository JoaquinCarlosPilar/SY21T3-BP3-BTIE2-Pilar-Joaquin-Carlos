#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

/*--------------------------------------------------------------------------------------------------------------------*/

class Bullet : public GameObject
{

public:

    // This is a constructor where we can specify the location, direction, and speed of the bullets
    Bullet(float positionX, float positionY, float directionX, float directionY, float speed);

    void start();
    void update();
    void draw();
    float getPostitionX();
    float getPositionY();
    float getWidth();
    float getHeight();

private:
SDL_Texture* texture;

int x;
int y;
int width;
int height;
int speed;

// This is the direction of the bullets that will fire off
float directionX;
float directionY;

};