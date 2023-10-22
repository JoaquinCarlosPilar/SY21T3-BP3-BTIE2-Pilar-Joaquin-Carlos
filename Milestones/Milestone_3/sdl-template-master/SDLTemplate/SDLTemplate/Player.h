#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "AltBullet.h"
#include "AltBullet2.h"
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

 // This tracks the position of the spaceship 
private:
    SDL_Texture* texture;
    Mix_Chunk* sound;

    int x;
    int y;
    int width;
    int height;
    int speed; 

    // This shows how long the player's reload time is (Bullet)
    float reloadTime;

    // This shows how many seconds from reloading are you in (Bullet)
    float currentReloadTime;

    // (AltBullet)
    float AltReloadTime;

    // (AltBullet)
    float AltCurrentReloadTime;

    // (AltBullet2)
    float AltReloadTime2;

    // (AltBullet2)
    float AltCurrentReloadTime2;

    std::vector<Bullet*> bullets;
    std::vector<AltBullet*> altbullets;
    std::vector<AltBullet2*> altbullets2;
};