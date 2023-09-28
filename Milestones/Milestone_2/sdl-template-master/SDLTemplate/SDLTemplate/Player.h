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

 // This tracks the position of the spaceship 
private:
    SDL_Texture* texture;
    Mix_Chunk* sound;

    int x;
    int y;
    int width;
    int height;
    int speed; 

    // This shows how long the player's reload time is
    float reloadTime;

    // This shows how many seconds from reloading are you in
    float currentReloadTime;

    std::vector<Bullet*> bullets;
};