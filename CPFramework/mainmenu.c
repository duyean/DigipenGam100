#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

CP_Image characterSheetImage;
CP_Image buttonUIImage;
CP_Image menuBackground;

Spritesheet characterSheet;
Animation characterAnimation;

Button playButton;
Button settingsButton;
Button quitButton;
float buttonHorizontalAlignment;
TextTemplate mainMenuTextTemplate;

int rowFrames[4] = { 0,1,0,1 };
int columnFrames[4] = { 0,0,1,1 };
float frameDuration = 15.f;

void main_menu_init(void) {
	CP_System_SetWindowSize(1600, 900);

	menuBackground = CP_Image_Load("./Assets/deepismLogo.png");

	mainMenuTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));
	buttonUIImage = CP_Image_Load("./Assets/MainMenuButton.png");
	CP_Font_Set(mainMenuTextTemplate.font);
	buttonHorizontalAlignment = 350.0f;

	characterSheetImage = CP_Image_Load("./Assets/WalkCycleSpriteSheet.png");
	characterSheet = CreateSpritesheet(characterSheetImage, 258, 258);
	characterAnimation = CreateAnimation(characterSheet, columnFrames, rowFrames, frameDuration,
		sizeof(columnFrames)/sizeof(columnFrames[0]), sizeof(rowFrames) / sizeof(rowFrames[0]));

	playButton = CreateButton(buttonHorizontalAlignment, 350, 480, 60, 255);
	playButton = AddTextToButton(&playButton, "Play", -100, 0);

	settingsButton = CreateButton(buttonHorizontalAlignment, 450, 480, 60, 255);
	settingsButton = AddTextToButton(&settingsButton, "Settings", -100, 0);

	quitButton = CreateButton(buttonHorizontalAlignment, 550, 480, 60, 255);
	quitButton = AddTextToButton(&quitButton, "Quit", -100, 0);

	CP_Settings_ImageMode(CP_POSITION_CENTER);
}

void main_menu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	DrawButtonUsingImage(buttonUIImage, &playButton, mainMenuTextTemplate);
	DrawButtonUsingImage(buttonUIImage, &settingsButton, mainMenuTextTemplate);
	DrawButtonUsingImage(buttonUIImage, &quitButton, mainMenuTextTemplate);
	
	//Animate(&characterAnimation, 800, 450);
	CP_Image_Draw(menuBackground, 1000, 400, 500, 500, 255);

	/*if (CP_Input_KeyReleased(KEY_Q)) {
		StartTransition();
	}*/
	TransitionFadeIn(1.f, 0,0,0, 255);
	//TransitionFadeOut(.5f, Settings);
}

void main_menu_exit(void) {
	//free(myImage);
}