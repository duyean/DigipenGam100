/*---------------------------------------------------------------
  File: animation.c
  Project: GAM100, Team ChocoMochiPie
  Author: Jerome
  Purpose: animation handler

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once

#include "animateClass.h" //required for Animation type

Animation Animation_Create(Spritesheet sheet, SpriteData const frames[], float animationSpeed, int numberOfSprites, int loop, int play);
/*Give initialized array to store the data*/
void Animation_SetFrames(int width, int height, float alpha, SpriteData* spriteArray, int horizontal, int vertical);
void Animation_Animate(Animation *animation, float x, float y, int flipX, int flipY);
/*Resets the specified Animation 'played' to 0 and 'frame' to 0*/
void Animation_Reset(Animation* animation);
/*Set the exact frame wanted in the animation*/
void Animation_SetFrame(Animation* animation, int index);
/*Sets the animation to Start or Stop Playing (This does not restart the animation)*/
void Animation_PlayState(Animation* animation, int state);