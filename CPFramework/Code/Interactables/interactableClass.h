#pragma once

#include "../CMP_Sprite_Pak.h"

typedef struct {
	float xPosition, yPosition;
	void (*OnInteract)(void);
	Spritesheet spritesheet;
}Interactable;