#pragma once

#include "../CMP_Sprite_Pak.h"

typedef struct {
	
	char* name;						//Used for Debugging
	float xPosition, yPosition;		//Used for the 'actual' position
	float drawXPos, drawYPos;		//Used for the 'draw' position
	float proximity;				//Used to check distance from player
	void (*OnInteract)(void);		//Used when Player interacts with Object
	Spritesheet spritesheet;
	SpriteData defaultSprite;
	int isAnimated;
	Animation animation;
}Interactable;