#pragma once

#include "cprocessing.h"

typedef struct {
	CP_Image source;		//The Loaded Image
	int width;				//The total Width of the Image
	int height;				//The total Height of the Image
	int spriteWidth;		//The Width of Each Sprite in the Image
	int spriteHeight;		//The Height of Each Sprite in the Image
}Spritesheet;

typedef struct {
	int row;				//The Row of the Sprite within the Spritesheet
	int column;				//The Column of the Sprite within the Spritesheet
	int width;				//The Expected Width of the Sprite, the Width that the Sprite will be drawn at
	int height;				//The Expected Height of the Sprite, the Height that the Sprite will be drawn at
}SpriteData;