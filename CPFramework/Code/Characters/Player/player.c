#include "cprocessing.h"
#include "../../CMP_Player_Pak.h"
#include "../../CMP_Sprite_Pak.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Interactable_Pak.h"
#include <stdio.h>
#include <math.h>

#define CHARACTER_SPRITES 4

//Player Stuff
Player* thisPlayer;
CP_Image characterSheetImage;
Spritesheet characterSheet;
Animation characterAnimation;
SpriteData characterSprites[CHARACTER_SPRITES];
float frameDuration = 15.f;

//Oil Stuff
CP_Image oilContainer;


void Player_Initialise(Player *player) {

	characterSheetImage = CP_Image_Load("./Assets/WalkCycleSpriteSheet_Reversed.png");
	oilContainer = CP_Image_Load("./Assets/Container.png");

	int characterSpriteDimension = CP_Image_GetWidth(characterSheetImage) / 2;
	int currentIndex = 0;
	for (int i = 0; i < CHARACTER_SPRITES / 2; i++) {
		for (int j = 0; j < CHARACTER_SPRITES / 2; j++) {
			characterSprites[currentIndex] = SpriteData_Create(characterSpriteDimension, characterSpriteDimension, j, i);
			currentIndex++;
		}
	}

	characterSheet = Spritesheet_Create(characterSheetImage, 258, 258);
	characterAnimation = Animation_Create(characterSheet, characterSprites, frameDuration, 4, 1, 1);

	player->currentPositionX = 0;
	player->currentPositionY = 0;
	player->movementSpeed = 100.f;
	player->faceDirection = 1;
	player->isInteracting = player->isMoving = 0;
	player->toDraw = 1;

	player->maxHealth = player->currentHealth = 2;
	player->maxStamina = player->currentStamina = 100.f;
	player->maxOil = 100.f;
	player->currentOil = 25.f;

	thisPlayer = player;
}

void Player_Update(Player *player) {
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(1453.f, 830.f - player->currentOil, 100.f, player->currentOil);
	CP_Image_Draw(oilContainer, 1500.f, 780.f, 180.f, 180.f, 255);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	if (!player->toDraw) return; //Check for whether player is hiding and therefore not drawn
	if (CP_Input_KeyDown(KEY_D)) {
		player->faceDirection = 1;
		player->isMoving = 1;
	}
	else if (CP_Input_KeyDown(KEY_A)) {
		player->faceDirection = -1;
		player->isMoving = 1;
	}
	else {
		player->isMoving = 0;
	}

	if (player->isMoving) {
		player->currentPositionX += player->faceDirection * player->movementSpeed * DeltaTime();
		Animation_Animate(&characterAnimation, 0, 0, player->faceDirection, 1);
	}
	else {
		Sprite_Draw(characterSheet, characterSprites[0], 0, 0, player->faceDirection, 1);
		if (CP_Input_KeyReleased(KEY_T)) {
			Animation_Reset(&characterAnimation);
		}
	}
}

void Player_CheckInteractables(Interactable *interactables[], int count) {
	if (CP_Input_KeyReleased(KEY_E)) {
		printf("\nAttempting Interaction!!!\n");
		for (int i = 0; i < count; i++) {
			Interactable* currInteractable = interactables[i];
			if (currInteractable->proximity > fabs(currInteractable->xPosition - thisPlayer->currentPositionX)) {
				//printf("PRINT FROM PLAYER.C -> Interact with %s\n", currInteractable->name);
				currInteractable->OnInteract();
			}
		}
	}
}

Spritesheet GetPlayerSheet(void) {
	return characterSheet;
}

Player* GetPlayer(void) {
	return thisPlayer;
}