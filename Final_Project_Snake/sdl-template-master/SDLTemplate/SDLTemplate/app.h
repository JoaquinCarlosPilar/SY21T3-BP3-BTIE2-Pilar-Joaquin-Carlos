#pragma once
#include "defs.h"
#include <SDL.h>

/*--------------------------------------------------------------------------------------*/

// Modified version of structs.h found in Parallel Realities
struct Texture {
	char name[MAX_NAME_LENGTH];
	SDL_Texture* texture;
	Texture* next;
};

/*--------------------------------------------------------------------------------------*/

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
	int keyboard[MAX_KEYBOARD_KEYS];
	Texture textureHead, * textureTail;
	char inputText[MAX_LINE_LENGTH];
} App;