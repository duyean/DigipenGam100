/*---------------------------------------------------------------
  File: mainmenu.c
  Project: GAM100, Team ChocoMochiPie
  Author: Breanne, Jerome
  Purpose: mainmenu scene

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "cprocessing.h"
#include "mainmenu.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Debug_Pak.h"
#include "../../CMP_Audio_Pak.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

CP_Image buttonUIImage, menuBackground;

Button playButton, settingsButton, quitButton, creditsButton;
float buttonHorizontalAlignment;
TextTemplate mainMenuTextTemplate;
SceneEnum nextScene;

void main_menu_init(void) {
	CP_System_SetWindowSize(1600, 900);

	menuBackground = CP_Image_Load("./Assets/Mainmenu.png");
	buttonUIImage = CP_Image_Load("./Assets/MainMenuButton.png");

	mainMenuTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));
	
	CP_Font_Set(mainMenuTextTemplate.font);

	buttonHorizontalAlignment = 350.0f;

	playButton = CreateButton(buttonHorizontalAlignment, 300, 480, 60, 255, &PlayButtonPressed);
	playButton = AddTextToButton(&playButton, "Play", -100, 0);

	settingsButton = CreateButton(buttonHorizontalAlignment, 400, 480, 60, 255, &SettingsButtonPressed);
	settingsButton = AddTextToButton(&settingsButton, "Settings", -100, 0);

	quitButton = CreateButton(buttonHorizontalAlignment, 500, 480, 60, 255, &QuitButtonPressed);
	quitButton = AddTextToButton(&quitButton, "Quit", -100, 0);

	creditsButton = CreateButton(buttonHorizontalAlignment, 600, 480, 60, 255, &CreditsButtonPressed);
	creditsButton = AddTextToButton(&creditsButton, "Credits", -100, 0);

	AudioInitialize();
	AudioPlayMainMenuMusic();

	CP_Settings_ImageMode(CP_POSITION_CENTER);
}

void main_menu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	CP_Image_Draw(menuBackground, 800.f, 450.f, 1600.f, 900.f, 255);

	DrawButtonUsingImage(buttonUIImage, &playButton, mainMenuTextTemplate);
	DrawButtonUsingImage(buttonUIImage, &settingsButton, mainMenuTextTemplate);
	DrawButtonUsingImage(buttonUIImage, &quitButton, mainMenuTextTemplate);
	DrawButtonUsingImage(buttonUIImage, &creditsButton, mainMenuTextTemplate);
	


	TransitionFadeIn(1.f, 0,0,0, 255);
	TransitionFadeOut(.5f, nextScene);

	if (IsDebugging()) {
		ShowDebugInfo();
	}

	if (CP_Input_KeyReleased(KEY_BACKSLASH)) {
		ToggleDebug();
	}
}

void main_menu_exit(void) {
	CP_Image_Free(menuBackground);
	CP_Image_Free(buttonUIImage);
	CP_Font_Free(mainMenuTextTemplate.font);

	// don't unload BGM pleaes -jelly
}

void PlayButtonPressed() {
	//printf("PlayerButtonPressed in mainmenu.c\n");

	AudioPlayGameplayMusic();

	StartTransition();
	nextScene = GAME;
}

void SettingsButtonPressed() {
	//printf("SettingsButtonPressed in mainmenu.c\n");
	StartTransition();
	nextScene = SETTINGS;
}

void QuitButtonPressed() {
	//printf("QuitButtonPressed in mainmenu.c\n");
	CP_Engine_Terminate();
}

void CreditsButtonPressed() {
	//printf("CreditsButtonPressed in mainmenu.c\n");
	StartTransition();
	nextScene = CREDITS;
}