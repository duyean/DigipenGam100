#pragma once
#include "utils.h"

typedef struct {
	float xPosition, yPosition;
	void (*OnInteract)(void);
	Spritesheet spritesheet;
}Interactable;

Interactable CreateInteractable(float xPos, float yPos, Spritesheet sheet, void (*OnInteract)(void));
void InteractionLocker(void);
void InteractionSludge(void);