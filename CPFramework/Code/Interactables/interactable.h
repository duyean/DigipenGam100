#pragma once
#include "interactableClass.h"

Interactable CreateInteractable(float xPos, float yPos, Spritesheet sheet, void (*OnInteract)(void));
void InteractionLocker(void);
void InteractionSludge(void);