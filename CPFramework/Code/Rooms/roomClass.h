#pragma once

#include "cprocessing.h"
#include "../CMP_Sprite_Pak.h"
#include "../CMP_Interactable_Pak.h"

typedef struct {
	Spritesheet roomComponents[6];
	SpriteData frame[6];
	int componentCount;
	Interactable *interractibles[4];
	int interactibleCount;
}Room;