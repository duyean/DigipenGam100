#include <stdio.h>
#include "cprocessing.h"
#include "player.h"
#include "../../CMP_Sprite_Pak.h"
#include "../../CMP_Core_Pak.h"


#define ArraySize(a) (sizeof(a)/sizeof(a[0]))

CP_Image characterSheetImage;
Spritesheet characterSheet;
Animation characterAnimation;
int rowFrames[4] = { 0,1,0,1 };
int columnFrames[4] = { 0,0,1,1 };
float frameDuration = 15.f;



//Extra that Edmund suggest to add something like this
//are we importing bool.h?
int KillPlayer(Player* player) {
	player->playerHealth = 0;
	if (player->playerHealth == 0)
	{
		return 1;
		//End the round
	}
	return 0;
}

float movementSpeed = 100.f;

void InitPlayer(Player *player) {
	characterSheetImage = CP_Image_Load("./Assets/WalkCycleSpriteSheet_Reversed.png");
	characterSheet = CreateSpritesheet(characterSheetImage, 258, 258);
	characterAnimation = CreateAnimation(characterSheet, columnFrames, rowFrames, frameDuration,
		ArraySize(columnFrames), ArraySize(rowFrames));

	player->currentPositionX = 800;
	player->currentPositionY = 450;
	player->faceDirection = 1;
	player->isInteracting = player->isMoving = 0;
}

void PlayerUpdate(Player *player) {
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
		player->currentPositionX += player->faceDirection * movementSpeed * DeltaTime();
		Animate(&characterAnimation, player->currentPositionX, player->currentPositionY, player->faceDirection, 1);
		printf("Player current position: %.3f\n", player->currentPositionX);
	}
	else {
		DrawSprite(characterSheet, 0, 0, player->currentPositionX, player->currentPositionY, player->faceDirection, 1);
	}
}

Spritesheet GetPlayerSheet(void) {
	return characterSheet;
}