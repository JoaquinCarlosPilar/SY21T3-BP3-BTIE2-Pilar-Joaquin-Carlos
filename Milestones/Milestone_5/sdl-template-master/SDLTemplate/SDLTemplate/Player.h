#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

/*--------------------------------------------------------------------------------------------------------------------*/

class Player : public GameObject
{
public:
    ~Player();
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    bool getIsAlive();
    void doDeath();

 // This tracks the position of the spaceship 
private:
    SDL_Texture* texture;
    Mix_Chunk* sound;

    int x;
    int y;
    int width;
    int height;
    int upspeed;
    int downspeed;
    int backwardspeed;
    int forwardspeed;
    int bulletspeed;

    // This shows how long the player's reload time is
    float reloadTime;

    // This shows how many seconds from reloading are you in
    float currentReloadTime;
    std::vector<Bullet*> bullets;

    // This checks if a player is alive or not
    bool isAlive;

};