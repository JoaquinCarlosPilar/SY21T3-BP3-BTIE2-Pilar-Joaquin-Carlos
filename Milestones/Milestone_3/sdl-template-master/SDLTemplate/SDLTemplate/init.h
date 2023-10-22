#pragma once
#include "common.h"
#include "app.h"

#include <SDL_image.h>
#include <SDL_mixer.h>

extern App app;

extern void initSDL(void);
extern void cleanup(void);