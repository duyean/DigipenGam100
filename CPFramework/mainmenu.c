#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

CP_Image myImage;
Spritesheet characterSheet;

void main_menu_init(void) {
	CP_System_SetWindowSize(1600, 900);

    // Load an image
    myImage = CP_Image_Load("./Assets/WalkCycleSpriteSheet.png");

	characterSheet = CreateSpritesheet(myImage, 256, 256);
}

void main_menu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(150, 150, 255, 255));
	CP_Graphics_DrawRectAdvanced(800,450, 200, 50,0,5);

    //CP_Image_Draw(myImage, 800, 450, CP_Image_GetWidth(myImage), CP_Image_GetHeight(myImage), 255);
	//CP_Image_DrawSubImage(myImage, 650, 450, 256, 256, 0, 0, 256, 256, 255);
	//CP_Image_DrawSubImage(myImage, 900, 450, 256, 256, 256, 256, 256*2, 256 * 2, 255);

	if (CP_Input_KeyDown(KEY_A)) {
		DrawSprite(characterSheet, 1 ,0, 800, 450);
	}
	else {
		DrawSprite(characterSheet, 1, 1, 800, 450);
	}
	

	if (CP_Input_KeyReleased(KEY_Q)) {
		StartTransition();
	}
	TransitionFadeIn(.5f, 0,0,0, 255);
	TransitionFadeOut(.5f, Settings);
}

void main_menu_exit(void) {
	//free(myImage);
}