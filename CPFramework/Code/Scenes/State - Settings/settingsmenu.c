#include "cprocessing.h"
#include "../../CMP_Scene_Pak.h"
#include <windows.h>
#include <stdio.h>

void settings_menu_init(void) {

}

void settings_menu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(200	, 200, 200, 255));



	
	if (CP_Input_KeyReleased(KEY_Q)) {
		StartTransition();
	}

	TransitionFadeIn(.5f, 0, 0, 0, 255);
	TransitionFadeOut(.5f, MAIN);
}

void settings_menu_exit(void) {

}