#include "cprocessing.h"
#include "sceneEnum.h"
#include "../CMP_Scene_Pak.h"
#include <stdio.h>
#include <math.h>

int isFadeIn = 0;
int isFadeOut = 0;
float transitionAlpha = 0;

/*
* SetScene takes in a sceneEnum
* Uses: Changes Scene
* Sub-uses: Used in main.c and FadeInOut Functions
*/
void SetScene(SceneEnum scene) {
	printf("\nChanging from Scene: %s\n", sceneNames[currentScene]);
	currentScene = scene;
	printf("Changing to Scene: %s\n\n", sceneNames[currentScene]);
	switch (scene){
	case INTRO:
		CP_Engine_SetNextGameState(intro_init, intro_update, intro_exit);
		break;
	case MAIN:
		CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
		break;
	case SETTINGS:
		CP_Engine_SetNextGameState(settings_menu_init, settings_menu_update, settings_menu_exit);
		break;
	case GAME:
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		break;
	default:
		printf("DEFAULT SET SCENE USED!!! CHECK FOR SWITCH FALL! OR NON-EXISTING ENUM!");
		CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
		break;
	}
}

/*
* TransitionFadeIn takes speed of the transition, RGBA of the transition colour
* Return: NIL
* Uses: Used to begin transition between scenes
* Fade from 0 to full colour alpha screen
* Sub-uses: NIL
*/
void TransitionFadeOut(float transitionSpeed, SceneEnum scene) {
	if (isFadeOut == 0) return;
	CP_Settings_NoStroke();
	transitionAlpha += transitionSpeed * DeltaTime();
	int alpha = CP_Math_LerpInt(0, 255, transitionAlpha);
	alpha = CP_Math_ClampInt(alpha, 0, 255);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, alpha));
	CP_Graphics_DrawRect(800, 450, 1600, 900);
	if (alpha >= 255) {
		isFadeOut = 0;
		isFadeIn = 1;
		printf("Fade Out Completed, Transition to Scene: %s\n", sceneNames[scene]);
		transitionToSceneFunc(scene);
	}
}

/*
* TransitionFadeIn takes speed of the transition, RGBA of the transition colour
* Return: NIL
* Uses: Should Only be used after a fullscreen effect
* Fade from full colour alpha screen to 0
* Sub-uses: NIL
*/
void TransitionFadeIn(float transitionSpeed, int r, int g, int b, int a) {
	if (isFadeIn == 0) return;
	CP_Settings_NoStroke();
	transitionAlpha -= transitionSpeed * DeltaTime();
	int alpha = CP_Math_LerpInt(0, a, transitionAlpha);
	alpha = CP_Math_ClampInt(alpha, 0, a);
	CP_Settings_Fill(CP_Color_Create(r, g, b, alpha));
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