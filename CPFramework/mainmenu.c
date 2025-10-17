#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include <windows.h>
#include <stdio.h>

void main_menu_init(void) {
	CP_System_SetWindowSize(1600, 900);
}

void main_menu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(150, 150, 255, 255));
	CP_Graphics_DrawRectAdvanced(800,450, 200, 50,0,5);

	if (CP_Input_KeyReleased(KEY_Q)) {
		StartTransition();
	}
	TransitionFadeIn(.5f);
	TransitionFadeOut(.5f, Settings);
}

void main_menu_exit(void) {

}