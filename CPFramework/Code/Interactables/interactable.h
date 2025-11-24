#pragma once
#include "interactableClass.h"
#include "../Characters/Player/playerClass.h"

/*Create an Interactable*/
void Interactable_Initialize(Interactable *interactable, float initialXPos, float initialYPos, float proximity, char* name,
	Spritesheet sheet, SpriteData defaultData, void (*OnInteract)(void));

/*Update the Position as well as any Sprite/Animation made to the Interactable*/
void Interactable_Update(Interactable* interactable, float xPos, float yPos);

/*Attaches an Animation to the Interactable if there are any*/
void Interactable_AttachAnimation(Interactable* interactable, Animation animation);

/*Create the Door Interactable, requires the image file path and Door Attributes and the respective interaction event*/
void Interactable_InitDoor(Interactable *door, float xPostion, float worldYPosition, void(*DoorInteractedEvent)(void));

/*Create the Oil Blob Interactable, requires the image file path and Blob Attributes and the respective interaction event*/
void Interactable_InitOilBlob(Interactable *blob,float xPostion, float worldYPosition, void(*DoorInteractedEvent)(void));

/*Create the Lift Interactable, requires the image file path and Lift Attributes and the respective interaction event*/
void Interactable_InitLift(Interactable *lift, float xPostion, float yPosition, void(*LiftInteractedEvent)(void));

/*The Specific Interaction for lockers; Hides the player and Plays an animation*/
void Interactable_DoorInteraction(Interactable* interactable, Player* player);
void Interactable_LiftInteraction(Interactable* interactable, Player* player);
void Interactable_OilInteraction(Interactable* interactable);

/*Initialise the Interactable Data to cache the data that will be used*/
void Interactable_InitialiseAssets(void);
void Interactable_Unload(void);