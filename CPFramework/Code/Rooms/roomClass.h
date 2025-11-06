#pragma once

#include "cprocessing.h"
#include "../CMP_Sprite_Pak.h"
#include "../CMP_Interactable_Pak.h"

typedef struct {
	Spritesheet room;
	SpriteData frame;
	int xPos;
	int yPos;
	Interactable interractibles[4];
	int interactibleCount;
}Room;