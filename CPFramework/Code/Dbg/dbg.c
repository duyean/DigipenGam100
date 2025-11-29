#pragma once
#include "cprocessing.h"
#include "../CMP_Scene_Pak.h" //used to get currentScene and sceneNames

int IsDebug = 0; //toggle here to change default debug state

void (*transitionToSceneFunc) (SceneEnum);
SceneEnum currentScene;

static void ShowCurrentScene(void) {

	CP_Font_DrawText("Current Scene: ", 120, 830);
	CP_Font_DrawText(sceneNames[currentScene], 120, 860);
}

void ShowDebugInfo(void) {
	CP_Settings_TextSize(40.0f);
	CP_Font_DrawText("Debug Info:", 100, 800);
	ShowCurrentScene();
}

int IsDebugging(void) {
	return IsDebug;
}

void ToggleDebug(void) {
	IsDebug = !IsDebug;
}