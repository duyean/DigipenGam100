#pragma once

#include "animateClass.h" //required for Animation type

Animation CreateAnimation(Spritesheet sheet, int cFrames[10], int rFrames[10], float animationSpeed, int cSize, int rSize);
void Animate(Animation *animation, float x, float y, int flipX, int flipY);