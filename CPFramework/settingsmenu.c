#include "cprocessing.h"
#include "utils.h"
#include <windows.h>
#include <stdio.h>

void settings_menu_init(void) {

}

void settings_menu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(200	, 200, 200, 255));
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(255, 150, 150, 255));
	CP_Graphics_DrawRectAdvanced(800, 450, 200, 50, 0, 5);

	
	if (CP_Input_KeyReleased(KEY_Q)) {
		StartTransition();
	}

	TransitionFadeIn(.5f, 0, 0, 0, 255);
	TransitionFadeOut(.5f, Main);
}

void settings_menu_exit(void) {

}