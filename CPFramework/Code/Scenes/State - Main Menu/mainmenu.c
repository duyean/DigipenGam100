#include "cprocessing.h"
#include "mainmenu.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Debug_Pak.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

CP_Image buttonUIImage;
CP_Image menuBackground;

Button playButton;
Button settingsButton;
Button quitButton;
float buttonHorizontalAlignment;
TextTemplate mainMenuTextTemplate;
SceneEnum nextScene;

extern CP_Sound mainMenuMusic;
extern CP_Sound gameplayMusic;
extern CP_Sound soundEffects;

extern float masterVolume;
extern float effectiveBGM;
extern float effectiveSFX;

void main_menu_init(void) {
	CP_System_SetWindowSize(1600, 900);

	menuBackground = CP_Image_Load("./Assets/deepismLogo.png");
	buttonUIImage = CP_Image_Load("./Assets/MainMenuButton.png");

	mainMenuTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));
	
	CP_Font_Set(mainMenuTextTemplate.font);

	buttonHorizontalAlignment = 350.0f;

	playButton = CreateButton(buttonHorizontalAlignment, 350, 480, 60, 255, &PlayButtonPressed);
	playButton = AddTextToButton(&playButton, "Play", -100, 0);

	settingsButton = CreateButton(buttonHorizontalAlignment, 450, 480, 60, 255, &SettingsButtonPressed);
	settingsButton = AddTextToButton(&settingsButton, "Settings", -100, 0);

	quitButton = CreateButton(buttonHorizontalAlignment, 550, 480, 60, 255, &QuitButtonPressed);
	quitButton = AddTextToButton(&quitButton, "Quit", -100, 0);

	mainMenuMusic = CP_Sound_Load("./Assets/Main.wav");
	CP_Sound_PlayAdvanced(mainMenuMusic, 1.0f, effectiveBGM, TRUE, CP_SOUND_GROUP_MUSIC);

	// plays when transitioning in PlayButtonPressed
	gameplayMusic = CP_Sound_Load("./Assets/Audio/Eerie.wav"); // the file locations need to be edited later after push

	CP_Settings_ImageMode(CP_POSITION_CENTER);
}

void main_menu_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	DrawButtonUsingImage(buttonUIImage, &playButton, mainMenuTextTemplate);
	DrawButtonUsingImage(buttonUIImage, &settingsButton, mainMenuTextTemplate);
	DrawButtonUsingImage(buttonUIImage, &quitButton, mainMenuTextTemplate);
	
	CP_Image_Draw(menuBackground, 1000.f, 400.f, 500.f, 500.f, 255.f);

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
	//free(myImage);
}

void PlayButtonPressed() {
	printf("PLayerButtonPressed in mainmenu.c\n");

	// jelly notes: DONT FREE THIS MUSIIIC
	// write up the logic for transitioning music later lalalalalaa
	CP_Sound_Free(mainMenuMusic);
	CP_Sound_PlayAdvanced(gameplayMusic, 0.1f, effectiveBGM, TRUE, CP_SOUND_GROUP_MUSIC);

	StartTransition();
	nextScene = GAME;
}

void SettingsButtonPressed() {
	printf("SettingsButtonPressed in mainmenu.c\n");
	StartTransition();
	nextScene = SETTINGS;
}

void QuitButtonPressed() {
	printf("QuitButtonPressed in mainmenu.c\n");
	//nextScene = QUIT;
	CP_Engine_Terminate();
}