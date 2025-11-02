#include "cprocessing.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Player_Pak.h"
#include "game.h"
#include <stdio.h>

CP_Color background;
Player player;
Camera* camera;
float playerX = 0, playerY = 0;
float lastPlayerX = 0, lastPlayerY = 0;


void game_init(void) {
	background = CP_Color_Create(150, 150, 150, 255);
	InitPlayer(&player);
	CreateCamera(&camera, player.currentPositionX, player.currentPositionY);
}

void game_update(void) {
	CP_Vector position = CP_Vector_Set(CP_System_GetWindowWidth() * .5f, CP_System_GetWindowHeight() * .5f);
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

	PlayerUpdate(&player);

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
	CP_Graphics_DrawRect(position.x-playerX, position.y-playerY, 50, 50);

	if (CP_Input_KeyReleased(KEY_Q)) {
		StartTransition();
	}

	TransitionFadeIn(.5f, 0, 0, 0, 255);
	TransitionFadeOut(.5f, MAIN);
}

void game_exit(void) {

}

void TestMidFunc(void) {
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Graphics_DrawRect(0, 0, 150, 150);
}