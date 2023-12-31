#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "AltBullet.h"
#include "AltBullet2.h"

/*--------------------------------------------------------------------------------------------------------------------*/

enum class Side
{
    PLAYER_SIDE,
    ENEMY_SIDE
};

/*--------------------------------------------------------------------------------------------------------------------*/

class Bullet : public GameObject
{
public:

    // This is a constructor where we can specify the location, direction, and speed of the bullets
    Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side);

    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();

    Side getSide();

private:
    SDL_Texture* texture;
    Side side;

    int x;
    int y;
    int width;
    int height;
    int speed;

    // This is the direction of the bullets that will fire off
    float directionX;
    float directionY;
};