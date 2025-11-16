#pragma once
//Solely to hold Scene Enum and Scene Names
typedef enum
{
	INTRO, MAIN, SETTINGS, GAME, PAUSE, CREDITS
}SceneEnum;

//Ensure Scene Names match respective enum values
static char* sceneNames[] = { "Intro", "Main", "Settings", "Game", "Pause", "Credits" };