#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

/*--------------------------------------------------------------------------------------------------------------------*/

class Player :
    public GameObject

{
public:
 void start();
 void update();
 void draw();

 // This tracks the position of the spaceship 
private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;
    int speed; 
};