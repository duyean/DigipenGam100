#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include "game.h"
#include "settingsmenu.h"
#include "intro.h"
#include <stdio.h>
#include <math.h>

int isFadeIn = 0;
int isFadeOut = 0;
float transitionAlpha = 0;
void (*transitionToSceneFunc) (SceneEnum);
SceneEnum currentScene;


//Initialize any utils, will be ran at main.c
void InitUtils(void) {
	transitionToSceneFunc = SetScene;
}

//### SCENE RELATED ###

//Sets scene according to enum found in utils.h
void SetScene(SceneEnum scene) {
	printf("Changing from Scene: %s\n", sceneNames[currentScene]);
	currentScene = scene;
	printf("Changing to Scene: %s\n", sceneNames[currentScene]);
	switch (scene){
	case Intro:
		CP_Engine_SetNextGameState(intro_init, intro_update, intro_exit);
		break;
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
void TransitionFadeIn(float transitionSpeed, int r, int g, int b, int a) {
	if (isFadeIn == 0) return;
	CP_Settings_NoStroke();
	transitionAlpha -= transitionSpeed * CP_System_GetDt();
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

int GetScreenHorizontalSize(void) {
	return 1600;
}

int GetScreenVerticalSize(void) {
	return 900;
}

//### SCENE RELATED END ###



//### USER INTERFACE RELATED ###

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	int withinX = click_x >= area_center_x - area_width / 2 && click_x <= area_center_x + area_width / 2;
	int withinY = click_y >= area_center_y - area_height / 2 && click_y <= area_center_y + area_height / 2;
	if (withinX && withinY) {
		return 1;
	}
	else {
		return 0;
	}
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	float radius = diameter / 2;
	return fabs((circle_center_x - click_x) * (circle_center_x - click_x) 
		+ (circle_center_y - click_y) * (circle_center_y - click_y)) 
		<= radius * radius;
}

CP_Image ButtonUsingImage(CP_Image loadedImage, float x, float y, float w, float h, int a) {
	if (loadedImage == NULL) return loadedImage;
	CP_Image_Draw(loadedImage, x, y, w, h, a);
	if (CP_Input_MouseClicked()) return loadedImage;
	if (IsAreaClicked(x, y, w, h, GetMouseClickPosition().x, GetMouseClickPosition().y)) {
		printf("This button pressed");
	}
	return loadedImage;
}

//### USER INTERFACE RELATED ###



//### SPRITE RELATED ###

Spritesheet CreateSpritesheet(CP_Image source, int w, int h) {
	Spritesheet sheet;
	sheet.source = source;
	sheet.width = CP_Image_GetWidth(source);
	sheet.height = CP_Image_GetHeight(source);
	sheet.spriteWidth = w;
	sheet.spriteHeight = h;

	return sheet;
}

void DrawSprite(Spritesheet sheet, int xRow, int rRow, int x, int y) {
	int horizontal = sheet.width / sheet.spriteWidth;
	int vertical = sheet.height / sheet.spriteHeight;

	int leftmostPixel = xRow * sheet.spriteWidth;
	int topMostPixel = rRow * sheet.spriteHeight;
	int rightMostPixel = leftmostPixel + sheet.spriteWidth;
	int bottomMostPixel = topMostPixel + sheet.spriteHeight;

	CP_Image_DrawSubImage(sheet.source, (float)x, (float)y, (float)sheet.spriteWidth, (float)sheet.spriteHeight,
		(float)leftmostPixel, (float)topMostPixel, (float)rightMostPixel, (float)bottomMostPixel, 255);
}

//### SPRITE RELATED END ###



//### INTERACTION RELATED ###

CP_Vector GetMouseClickPosition(void) {
	return CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
}

//### INTERACTION RELATED END ###
