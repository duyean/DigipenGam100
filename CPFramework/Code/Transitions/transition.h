#pragma once

#include "sceneEnum.h" //required for SceneEnum type

void SetScene(SceneEnum scene);
void TransitionFadeIn(float transitionSpeed, int r, int g, int b, int a);
void TransitionFadeOut(float, SceneEnum);
void StartTransition(void);