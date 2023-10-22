#pragma once

#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'
#define WINDOW_NAME				"BASPRG3 SDL TEMPLATE"
#define FPS                      60
#define MAX_KEYBOARD_KEYS        350
#define MAX_NAME_LENGTH          32
#define MAX_LINE_LENGTH          1024

#define SCREEN_WIDTH             1280
#define SCREEN_HEIGHT            720

#define MAX_SND_CHANNELS         8

#define GLYPH_HEIGHT             28
#define GLYPH_WIDTH              18

enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};