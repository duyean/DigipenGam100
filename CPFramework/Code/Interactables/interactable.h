#pragma once
#include "interactableClass.h"
#include "../Characters/Player/playerClass.h"

/*Create an Interactable*/
Interactable Interactable_Create(float initialXPos, float initialYPos, float proximity, char* name,
	Spritesheet sheet, SpriteData defaultData, void (*OnInteract)(void));

/*Update the Position as well as any Sprite/Animation made to the Interactable*/
void Interactable_Update(Interactable* interactable, float xPos, float yPos);

/*Attaches an Animation to the Interactable if there are any*/
void Interactable_AttachAnimation(Interactable* interactable, Animation animation);

/*The Specific Interaction for lockers; Hides the player and Plays an animation*/
void InteractionLocker(Interactable* interactable, Player* player);
void InteractionSludge(void);