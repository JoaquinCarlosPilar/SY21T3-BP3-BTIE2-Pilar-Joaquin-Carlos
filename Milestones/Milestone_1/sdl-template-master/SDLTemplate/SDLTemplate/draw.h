#pragma once
#include <SDL_image.h>
#include "common.h"
#include "app.h"

extern App app;

extern void prepareScene(void);
extern void presentScene(void);
static SDL_Texture* getTexture(char* name);
static void addTextureToCache(char* name, SDL_Texture* sdlTexture);
SDL_Texture* loadTexture(const char* filename);
extern void blit(SDL_Texture* texture, int x, int y);
extern void blitRotate(SDL_Texture* texture, int x, int y, double angle);
extern void blitScale(SDL_Texture* texture, int x, int y, int* width, int* height, int scale);
void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y);