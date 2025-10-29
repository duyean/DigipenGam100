#pragma once
//Solely to hold Scene Enum and Scene Names
typedef enum
{
	INTRO, MAIN, SETTINGS, GAME, PAUSE
}SceneEnum;

//Ensure Scene Names match respective enum values
static char* sceneNames[] = { "Intro", "Main", "Settings", "Game", "Pause" };