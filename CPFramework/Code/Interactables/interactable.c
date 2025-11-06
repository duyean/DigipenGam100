#include <stdio.h>
#include "cprocessing.h"
#include "../CMP_Interactable_Pak.h"
#include "../CMP_Sprite_Pak.h"
#include "../CMP_Player_Pak.h"

CP_Image lockerImage;
Spritesheet lockerSpritesheet;
SpriteData lockerStateSprites[2];

Interactable Interactable_Create(float initialXPos, float initialYPos, float proximity, char* name, 
	Spritesheet sheet, SpriteData defaultSprite, void (*OnInteract)(void)) {
	static Interactable newInteractable;
	newInteractable.xPosition = newInteractable.drawXPos = initialXPos;
	newInteractable.yPosition = newInteractable.drawYPos = initialYPos;
	newInteractable.proximity = proximity;
	newInteractable.name = name == NULL ? "Unnamed Interactable" : name;
	newInteractable.spritesheet = sheet;
	newInteractable.defaultSprite = defaultSprite;
	newInteractable.OnInteract = OnInteract;

	newInteractable.isAnimated = 0;
	return newInteractable;
}

void Interactable_AttachAnimation(Interactable* interactable, Animation animation) {
	interactable->isAnimated = 1;
	interactable->animation = animation;
}

void Interactable_Update(Interactable *interactable, float xPos, float yPos) {
	interactable->drawXPos = xPos;
	interactable->drawYPos = yPos;
	if (interactable->isAnimated) {
		Animation_Animate(&interactable->animation, xPos, yPos, 1, 1);
	}
	else {
		Sprite_Draw(interactable->spritesheet, interactable->defaultSprite, interactable->drawXPos, interactable->drawYPos, 1, 1);
	}
}

void InteractionLocker(Interactable *interactable, Player *player) {
	printf("Interacted with: %s\n", interactable->name);
	player->toDraw = !player->toDraw;
	Animation_Reset(&interactable->animation);
	Animation_PlayState(&interactable->animation, 1);
}

void InteractionSludge(void) {
	GetPlayer()->currentOil += 10.f;
	GetPlayer()->currentOil = CP_Math_ClampFloat(GetPlayer()->currentOil, 0.f, GetPlayer()->maxOil);
}