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

/*Create the Door Interactable, requires the image file path and Door Attributes and the respective interaction event*/
Interactable Interactable_CreateDoor(float xPostion, float worldYPosition, void(*DoorInteractedEvent)(void));

/*Create the Oil Blob Interactable, requires the image file path and Blob Attributes and the respective interaction event*/
Interactable Interactable_CreateOilBlob(float xPostion, float worldYPosition, void(*DoorInteractedEvent)(void));

/*The Specific Interaction for lockers; Hides the player and Plays an animation*/
void Interactable_DoorInteraction(Interactable* interactable, Player* player);
void Interactable_OilInteraction(void);

/*Initialise the Interactable Data to cache the data that will be used*/
void Interactable_InitialiseData(void);
void Interactabe_FreeData(void);