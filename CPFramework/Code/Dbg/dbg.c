#pragma once
#include "cprocessing.h"
#include "../CMP_Scene_Pak.h" //used to get currentScene and sceneNames

int IsDebug = 0; //toggle here to change default debug state

void (*transitionToSceneFunc) (SceneEnum);
SceneEnum currentScene;

static void ShowCurrentScene(void) {

	CP_Font_DrawText("Current Scene: ", 1480, 820);
	CP_Font_DrawText(sceneNames[currentScene], 1540, 820);
}

void ShowDebugInfo(void) {
	CP_Settings_TextSize(15.0f);
	CP_Font_DrawText("Debug Info:", 1500, 800);
	ShowCurrentScene();
}

int IsDebugging(void) {
	return IsDebug;
}

void ToggleDebug(void) {
	IsDebug = !IsDebug;
}