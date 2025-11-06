#pragma once
#include "interactableClass.h"
#include "../Characters/Player/playerClass.h"

Interactable Interactable_Create(float initialXPos, float initialYPos, float proximity, char* name,
	Spritesheet sheet, SpriteData defaultData, void (*OnInteract)(void));
void Interactable_Update(Interactable* interactable, float xPos, float yPos);
void Interactable_AttachAnimation(Interactable* interactable, Animation animation);
void InteractionLocker(Interactable* interactable, Player* player);
void InteractionSludge(void);