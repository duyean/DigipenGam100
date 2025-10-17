#pragma once

typedef enum 
{
	Main, Settings, Game
}SceneEnum;

void SetScene(SceneEnum scene);
void TransitionFadeIn(float);
void TransitionFadeOut(float, SceneEnum);
void InitUtils(void);
void StartTransition(void);
//Ignore for now, might have use later
//typedef struct {
//	FunctionPtr init;
//	FunctionPtr update;
//	FunctionPtr exit;
//}Scene;