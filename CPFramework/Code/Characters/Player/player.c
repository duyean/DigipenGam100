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
CP_Image oilContainerImage;
float oilImageX, oilImageY;
Spritesheet oilContainerSheet;
SpriteData oilContainerSprite;

//Stamina Stuff
CP_Image staminaBarImage;
Spritesheet staminaBarSheet;
SpriteData staminaBarSprite;
float staminaDrawAlpha = 255.f;


//Extra that Edmund suggest to add something like this
//are we importing bool.h?




void Player_Initialise(Player *player) {

	//Initialise Character
	characterSheetImage = CP_Image_Load("./Assets/WalkCycleSpriteSheet_Reversed.png");

	int characterSpriteDimension = CP_Image_GetWidth(characterSheetImage) / 2;
	Animation_SetFrames(characterSpriteDimension, characterSpriteDimension, 255.f, characterSprites, 2, 2);

	characterSheet = Spritesheet_Create(characterSheetImage, 258, 258);
	characterAnimation = Animation_Create(characterSheet, characterSprites, frameDuration, 4, 1, 1);

	player->currentPositionX = 0;
	player->currentPositionY = 0;
	player->movementSpeed = 100.f;
	player->movementMultiplier = 1.f;
	player->faceDirection = 1;
	player->isInteracting = player->isMoving = 0;
	player->toDraw = 1;
	player->isHiding = 0;

	player->maxHealth = player->currentHealth = 1;
	player->maxStamina = player->currentStamina = 100.f;
	player->maxOil = 100.f;
	player->currentOil = 0.f;

	thisPlayer = player;


	//Initialise Stamina Bar
	staminaBarImage = CP_Image_Load("./Assets/Stamina.png");
	staminaBarSheet = Spritesheet_Create(staminaBarImage, 1600, 50);
	staminaBarSprite = SpriteData_Create(1600, 50, 0, 0, 255.f);


	//Initialise Oil Bar
	oilContainerImage = CP_Image_Load("./Assets/Container.png");
	oilContainerSheet = Spritesheet_Create(oilContainerImage, 512, 512);
	oilContainerSprite = SpriteData_Create(180, 180, 0, 0, 255.f);
	oilImageX = 700.f;
	oilImageY = 330.f;
}

void Player_Update(Player *player) {
	
	Player_OilUpdate(player);
	Player_StaminaUpdate(player);

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
		player->currentPositionX += player->faceDirection * player->movementSpeed * player->movementMultiplier * DeltaTime();
		Animation_Animate(&characterAnimation, 0, 0, player->faceDirection, 1);
		if (CP_Input_KeyDown(KEY_LEFT_SHIFT) && player->currentStamina > 0) {
			float encumberance = player->currentOil / player->maxOil * 10.f;
			printf("Current encumberance: %.2f\n", encumberance);
			player->currentStamina -= (45.f + encumberance) * DeltaTime();
			player->movementMultiplier = 2.5f;
	}	}
	else {
		Sprite_Draw(characterSheet, characterSprites[0], 0, 0, player->faceDirection, 1);
	}

	if (CP_Input_KeyTriggered(KEY_LEFT_SHIFT) && player->currentStamina > 0)
	{
		player->currentStamina -= 15.f;
	}
	if (CP_Input_KeyReleased(KEY_LEFT_SHIFT) || player->currentStamina <= 0) {
	
		player->movementMultiplier = 1.f;
	}

	//DEBUG
	if (CP_Input_KeyReleased(KEY_K)) {
		player->currentOil += 10.f;
	}
}

void Player_CheckInteractables(Interactable *interactables[], int count, float relativePosition) {
	if (CP_Input_KeyReleased(KEY_E)) {
		printf("\nAttempting Interaction!!!\n");
		for (int i = 0; i < count; i++) {
			Interactable* currInteractable = interactables[i];
			float globalPosition = relativePosition + currInteractable->worldXPosition;
			if (currInteractable->proximity > fabs(globalPosition - thisPlayer->currentPositionX)) {
				//printf("PRINT FROM PLAYER.C -> Interact with %s from Position: %f\n", currInteractable->name, currInteractable->worldXPosition);
				currInteractable->OnInteract();
				printf("ALLOWS = Interact with %s from Position: %.3f with offset of %.3f\n", currInteractable->name, globalPosition, currInteractable->proximity);
			}
			printf("Active Interractible at Position: %.3f\n", globalPosition);
		}
		printf("Player Position: %.3f\n", thisPlayer->currentPositionX);
	}
}

void Player_StaminaUpdate(Player *player) {
	player->currentStamina += 10.f * DeltaTime();
	player->currentStamina = CP_Math_ClampFloat(player->currentStamina, 0.f, 100.f);
	if (player->currentStamina >= player->maxStamina) {
		staminaDrawAlpha -= 255.f * DeltaTime();
	}
	else {
		staminaDrawAlpha += 1000.f * DeltaTime();
	}
	staminaDrawAlpha = CP_Math_ClampFloat(staminaDrawAlpha, 0.f, 150.f);
	SpriteData_Update(&staminaBarSprite, 1200.f * (player->currentStamina / player->maxStamina), 30, staminaDrawAlpha);
	Sprite_Draw(staminaBarSheet, staminaBarSprite, 0, 400, 1, 1);

	/*This is for testing and should be removed*/
	if (CP_Input_KeyDown(KEY_SPACE)) {
		player->currentStamina = 100.f;
	}
}

void Player_OilUpdate(Player* player) {
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(750.f + oilImageX, 500.f + oilImageY, 100.f, -player->currentOil);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	Sprite_Draw(oilContainerSheet, oilContainerSprite, oilImageX, oilImageY, 1, 1);
}

void Player_Unload(void) {
	CP_Image_Free(characterSheetImage);
	CP_Image_Free(oilContainerImage);
	CP_Image_Free(staminaBarImage);
}

Spritesheet GetPlayerSheet(void) {
	return characterSheet;
}

Player* GetPlayer(void) {
	return thisPlayer;
}