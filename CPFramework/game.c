#include "cprocessing.h"
#include "utils.h"
#include "player.h"
#include "camera.h"
#include "game.h"
#include <stdio.h>

CP_Color background;
Player player;

void game_init(void) {
	background = CP_Color_Create(150, 150, 150, 255);
	InitPlayer(&player);
}

void game_update(void) {
	CP_Vector position = CP_Vector_Set(CP_System_GetWindowWidth() * .5f, CP_System_GetWindowHeight() * .5f);
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

	MoveCamera(player.currentPositionX, player.currentPositionY, &TestMidFunc);

	PlayerUpdate(&player);

	// Draw a red box in the center of the screen
	CP_Settings_Fill(CP_Color_Create(255, 100, 255, 255));
	CP_Graphics_DrawRect(position.x, position.y, 50, 50);

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