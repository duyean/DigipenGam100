#include "cprocessing.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Player_Pak.h"
#include "../../CMP_Interactable_Pak.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

#define INTERACTABLES_COUNT 2

CP_Color background;
Player player;
Camera* camera;
float playerX = 0, playerY = 0;
float lastPlayerX = 0, lastPlayerY = 0;

Interactable *interactablesArray[INTERACTABLES_COUNT];

Interactable interactableOil;
Spritesheet oilSpritesheet;
SpriteData oilSprite;
CP_Image oilImage;

CP_Image lockerImage;
Interactable locker;
Spritesheet lockerSheet;
SpriteData lockerSprites[2];
Animation lockerAnimation;

CP_Vector worldCenterPosition;


//Just to reduce the printf occurence
float lastFrameTime = 0;


/*UPDATE THE ADDRESS HANDLING FOR INTERACTABLES*/

/*Functions here are for testing and can be removed for FINAL*/
void InitialiseInteractables(void);
void LockerTest(void);

void game_init(void) {
	background = CP_Color_Create(150, 150, 150, 255);
	Player_Initialise(&player);
	CreateCamera(&camera, player.currentPositionX, player.currentPositionY);

	worldCenterPosition = CP_Vector_Set(CP_System_GetWindowWidth() * .5f, CP_System_GetWindowHeight() * .5f);

	InitialiseInteractables();
}

void game_update(void) {
	
	CP_Vector centerOfScreen = CP_Vector_Set(CP_System_GetWindowWidth() * .5f, CP_System_GetWindowHeight() * .5f);
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

	CP_Graphics_DrawRect(centerOfScreen.x - playerX, centerOfScreen.y - playerY, 50, 50);

	for (int i = 0; i < INTERACTABLES_COUNT; i++) {
		Interactable_Update(interactablesArray[i], interactablesArray[i]->xPosition - playerX, interactablesArray[i]->yPosition - playerY);
	}

	Player_Update(&player);
	/*TO BE UPDATED: SLOT FUNCTION FOR CURRENT ROOM - J*/
	Player_CheckInteractables(interactablesArray, INTERACTABLES_COUNT);

	// Calculate player movement delta (velocity) since last frame
	playerX = player.currentPositionX;
	playerY = player.currentPositionY;
	float dx = playerX - lastPlayerX;  // playerDX: horizontal movement from last frame
	float dy = playerY - lastPlayerY;  // playerDY: vertical movement from last frame
	lastPlayerX = playerX;
	lastPlayerY = playerY;

	UpdateCamera(&camera, player.currentPositionX, player.currentPositionY, dx, dy, 0.1f); //test case, please edit later. Read camera.c for more info. -day

	/*
	using parallex code here for background layers later
	if you can't do it then say i guess. 
	I think I made it ok to follow.
													-day
	*/

	// Draw a red box in the center of the screen
	CP_Settings_Fill(CP_Color_Create(255, 100, 255, 255));

	TransitionFadeIn(.5f, 0, 0, 0, 255);
	TransitionFadeOut(.5f, MAIN);

	/*if (lastFrameTime <= CP_System_GetSeconds()) {
		lastFrameTime = CP_System_GetSeconds() + CP_System_GetDt();
		printf("Current Player X Position: %.3f\n", playerX);
	}*/
}

void game_exit(void) {

}

void InitialiseInteractables(void) {
	oilImage = CP_Image_Load("Assets/ChocoMochiPie.png");
	lockerImage = CP_Image_Load("Assets/LockerSpritesheet.png");

	lockerSheet = Spritesheet_Create(lockerImage, CP_Image_GetWidth(lockerImage) / 2, CP_Image_GetHeight(lockerImage));
	lockerSprites[0] = SpriteData_Create(100, 200, 0, 0);
	lockerSprites[1] = SpriteData_Create(100, 200, 1, 0);
	lockerAnimation = Animation_Create(lockerSheet, lockerSprites, 25.f, 2, 0, 0);
	locker = Interactable_Create(0, 0, 100.f, "Locker", lockerSheet, lockerSprites[0], &LockerTest);
	Interactable_AttachAnimation(&locker, lockerAnimation);

	interactablesArray[0] = &locker;

	oilSprite = SpriteData_Create(200, 200, 0, 0);
	oilSpritesheet = Spritesheet_Create(oilImage, 1000, 1000);
	interactableOil = Interactable_Create(300.f, 0.f, 100.f, "Sludge 1", oilSpritesheet, oilSprite, &InteractionSludge);
	interactablesArray[1] = &interactableOil;
}

void LockerTest(void) {
	InteractionLocker(&locker, &player);
}