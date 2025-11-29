/*---------------------------------------------------------------
  File: interactables.c
  Project: GAM100, Team ChocoMochiPie
  Author: Jerome, Daniel, Edmund
  Purpose: interactable objects in the map

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include <stdio.h>
#include "cprocessing.h"
#include "../CMP_Interactable_Pak.h"
#include "../CMP_Sprite_Pak.h"
#include "../CMP_Player_Pak.h"
#include "../CMP_Audio_Pak.h"

float interactableProximity = 100.f;

void Interactable_Initialize(Interactable *interactable, float initialXPos, float initialYPos, float proximity, char* name, 
	Spritesheet sheet, SpriteData defaultSprite, void (*OnInteract)(void)) {
	interactable->worldXPosition = initialXPos;
	interactable->worldYPosition = initialYPos;
	interactable->drawXPos = initialXPos;
	interactable->drawYPos = initialXPos;
	interactable->proximity = proximity;
	interactable->name = name == NULL ? "Unnamed Interactable" : name;
	interactable->spritesheet = sheet;
	interactable->defaultSprite = defaultSprite;
	interactable->OnInteract = OnInteract;
	interactable->toDraw = 1;
	interactable->oilAmount = 30.0f; //Oil amount change as you need tbh
	interactable->isAnimated = 0;
}

void Interactable_AttachAnimation(Interactable* interactable, Animation animation) {
	interactable->isAnimated = 1;
	interactable->animation = animation;
}

void Interactable_Update(Interactable *interactable, float xPos, float yPos) {
	interactable->drawXPos = xPos;
	interactable->drawYPos = yPos;
	/*interactable->worldXPosition = xPos;
	interactable->worldYPosition = yPos;*/
	if (interactable->toDraw == 1)
	{
		if (interactable->isAnimated) {
			Animation_Animate(&interactable->animation, xPos, yPos, 1, 1);
		}
		else {
			Sprite_Draw(interactable->spritesheet, interactable->defaultSprite, (int)interactable->drawXPos, (int)interactable->drawYPos, 1, 1);
		}
	}
}

CP_Image doorImage, blobImage, liftImage;
Spritesheet doorSpritesheet, blobSpritesheet, liftSpritesheet;
SpriteData doorSprites[2], blobSprites[4], liftSprites[2];
Animation doorAnimation, blobAnimation, liftAnimation;

// no variety yet -jelly
CP_Sound oilSFX = NULL;
CP_Sound doorElevatorSFX = NULL; 
CP_Sound footstepsSFX = NULL;

void Interactable_InitialiseAssets(void) {
	/*Initialise Door Data Here*/
	doorImage = CP_Image_Load("./Assets/LockerSpritesheet.png");
	doorSpritesheet = Spritesheet_Create(doorImage, CP_Image_GetWidth(doorImage) / 2, CP_Image_GetHeight(doorImage));
	Animation_SetFrames(100, 200, 255.f, doorSprites, 2, 1);
	doorAnimation = Animation_Create(doorSpritesheet, doorSprites, 15.f, 2, 0, 0);

	/*Initialise Oil Blob Data Here*/
	blobImage = CP_Image_Load("./Assets/BlobSprite.png");
	blobSpritesheet = Spritesheet_Create(blobImage, 514, 514);
	Animation_SetFrames(200, 200, 255.f, blobSprites, 2, 2);
	blobAnimation = Animation_Create(blobSpritesheet, blobSprites, 30.f, 2, 1, 1);

	/*Initialise lift Data Here*/
	liftImage = CP_Image_Load("./Assets/LiftSpriteSheet2.png");
	liftSpritesheet = Spritesheet_Create(liftImage, CP_Image_GetWidth(liftImage) / 2, CP_Image_GetHeight(liftImage));
	Animation_SetFrames(375, 900, 255.f, liftSprites, 2, 1);
	liftAnimation = Animation_Create(liftSpritesheet, liftSprites, 15.f, 2, 0, 0);

	// cp sound load doesnt load anything BUT wav lmao fucking hell
	oilSFX = CP_Sound_Load("./Assets/Audio/Oil_Pickup.wav");
	doorElevatorSFX = CP_Sound_Load("./Assets/Audio/Door_Elevator.wav");
	footstepsSFX = CP_Sound_Load("./Assets/Audio/Footstep_1.wav");
}

void Interactable_Unload(void) {
	CP_Image_Free(doorImage);
	CP_Image_Free(blobImage);
	CP_Image_Free(liftImage);

	CP_Sound_Free(oilSFX);
	CP_Sound_Free(doorElevatorSFX);
	CP_Sound_Free(footstepsSFX);
}

void Interactable_InitDoor(Interactable *door, float xPostion, float worldYPosition, void(*DoorInteractedEvent)(void)) {
	Interactable_Initialize(door, xPostion, worldYPosition, interactableProximity, "Locker", doorSpritesheet, doorSprites[0], DoorInteractedEvent);
	Interactable_AttachAnimation(door, doorAnimation);
}

void Interactable_InitOilBlob(Interactable *blob, float xPostion, float worldYPosition, void(*BlobInteractedEvent)(void)) {
	Interactable_Initialize(blob ,xPostion, worldYPosition, interactableProximity, "Oil", blobSpritesheet, blobSprites[0], BlobInteractedEvent);
	Interactable_AttachAnimation(blob, blobAnimation);
}

void Interactable_InitLift(Interactable *lift, float xPostion, float yPosition, void(*LiftInteractedEvent)(void)) {
	Interactable_Initialize(lift, xPostion, yPosition, interactableProximity, "Lift", liftSpritesheet, liftSprites[0], LiftInteractedEvent);
	Interactable_AttachAnimation(lift, liftAnimation);
}

void Interactable_DoorInteraction(Interactable *interactable, Player *player) {

	AudioPlaySFX(doorElevatorSFX);

	player->isHiding = !player->isHiding;
	player->toDraw = !player->toDraw;
	Animation_Reset(&interactable->animation);
	Animation_PlayState(&interactable->animation, 1);
}

void Interactable_OilInteraction(Interactable* interactable) {

	//CHANGE THIS TO BE ON THE PLAYER AND NOT ON THE INTERACTABLE SCRIPT
	if (interactable->toDraw == 1)
	{
		AudioPlaySFX(oilSFX);

		GetPlayer()->currentOil += 10.f;
		interactable->oilAmount -= 10.f;
		GetPlayer()->currentOil = CP_Math_ClampFloat(GetPlayer()->currentOil, 0.f, GetPlayer()->maxOil);
		
		if (interactable->oilAmount <= 0.f)
		{
			interactable->toDraw = 0;
		}
	}
}

void Interactable_LiftInteraction(Interactable* interactable, Player* player) {

	AudioPlaySFX(doorElevatorSFX);

	player->isHiding = !player->isHiding;

	Animation_Reset(&interactable->animation);
	Animation_PlayState(&interactable->animation, 1);
	player->toDraw = !player->toDraw;
}