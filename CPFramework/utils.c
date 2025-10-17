#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include "game.h"
#include "settingsmenu.h"
#include <stdio.h>

int isFadeIn = 0;
int isFadeOut = 0;

float transitionAlpha = 0;

void (*transitionToSceneFunc) (SceneEnum);

//Initialize any utils, will be ran at main.c
void InitUtils(void) {
	transitionToSceneFunc = SetScene;
}

//Sets scene according to enum found in utils.h
void SetScene(SceneEnum scene) {
	//printf("Changing to: %d\n", scene);
	switch (scene){
	case Main:
		CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
		break;
	case Settings:
		CP_Engine_SetNextGameState(settings_menu_init, settings_menu_update, settings_menu_exit);
		break;
	case Game:
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	default:
		CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
		break;
	}
}

//TransitionFadeOut takes:
//1. The Speed of the Transition as a float
//2. The Scene to Transition To
//Lerps a black fullscreen rectangle from 0 to 255 alpha 
void TransitionFadeOut(float transitionSpeed, SceneEnum scene) {
	if (isFadeOut == 0) return;
	CP_Settings_NoStroke();
	transitionAlpha += transitionSpeed * CP_System_GetDt();
	int alpha = CP_Math_LerpInt(0, 255, transitionAlpha);
	alpha = CP_Math_ClampInt(alpha, 0, 255);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, alpha));
	CP_Graphics_DrawRect(800, 450, 1600, 900);
	if (alpha >= 255) {
		isFadeOut = 0;
		isFadeIn = 1;
		printf("Fade Out Completed, Transition to Scene: %d\n", scene);
		transitionToSceneFunc(scene);
	}
}

//TransitionFadeIn takes:
//1. The Speed of the Transition as a float
//Lerps a black fullscreen rectangle from 255 to 0 alpha 
void TransitionFadeIn(float transitionSpeed) {
	if (isFadeIn == 0) return;
	CP_Settings_NoStroke();
	transitionAlpha -= transitionSpeed * CP_System_GetDt();
	int alpha = CP_Math_LerpInt(0, 255, transitionAlpha);
	alpha = CP_Math_ClampInt(alpha, 0, 255);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, alpha));
	CP_Graphics_DrawRect(800, 450, 1600, 900);
	if (alpha <= 0) {
		printf("Fade In Completed\n");
		isFadeIn = 0;
	}
}

//Manually Start the transition
void StartTransition(void) {
	if (isFadeOut == 1 || isFadeIn == 1) return;
	isFadeOut = 1;
}

int GetScreenHorizontalSize(void) {
	return 1600;
}

int GetScreenVerticalSize(void) {
	return 900;
}