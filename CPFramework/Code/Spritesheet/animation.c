/*---------------------------------------------------------------
  File: animation.c
  Project: GAM100, Team ChocoMochiPie
  Author: Jerome
  Purpose: animation handler

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "../CMP_Sprite_Pak.h"
#include "../CMP_Core_Pak.h"
#include <stdio.h>

/*
*
* Uses Init 'Spritesheet', the array format of each frame in order, the time between frames, and size each dimension
* Return: Initialized Animation
* Uses : To Create references to animation
* Sub - uses : NIL
*/
Animation Animation_Create(Spritesheet sheet, SpriteData frames[], float animationSpeed, int numberOfSprites, int loop, int playing) {
	static Animation newAnimation;
	newAnimation.frameDuration = animationSpeed;
	newAnimation.frames = frames;
	newAnimation.sheet = sheet;
	newAnimation.currFrameIndex = 0;
	newAnimation.noOfSprites = numberOfSprites;
	newAnimation.toLoop = loop;
	newAnimation.played = 0;
	newAnimation.isPlaying = playing;
	return newAnimation;
}

void Animation_SetFrames(int width, int height, float alpha, SpriteData* spriteArray, int horizontal, int vertical) {
	int index = 0;
	for (int i = 0; i < vertical; i++) {
		for (int j = 0; j < horizontal; j++) {
			spriteArray[index++] = SpriteData_Create(width, height, j, i, alpha);
		}
	}
}

/*
* Animation_Animate takes in a 'Animation' Pointer as a source, the x and y position of the animation and the ElapsedTimeSeconds of the game
* Returns: NIL
* Uses: To Animation_Animate the passed in animation of whatever game object
* Sub-uses: NIL
*/
void Animation_Animate(Animation* animation, float xPos, float yPos, int flipX, int flipY) {
	float currentTime = ElapsedTimeSeconds();
	if (animation->lastFrameTime <= currentTime && animation->played == 0 && animation->isPlaying == 1) {
		animation->lastFrameTime = currentTime + animation->frameDuration * DeltaTime();
		animation->currFrameIndex++;

		if (animation->currFrameIndex >= animation->noOfSprites) {
			animation->currFrameIndex = 0;
			if (!animation->toLoop) {
				animation->played = 1;
				animation->isPlaying = 0;
			}
		}

		/*printf("Current Row: %d, Current Column: %d\n", animation->frames[animation->currFrameIndex].row,
			animation->frames[animation->currFrameIndex].column);*/
	}
	Sprite_Draw(animation->sheet, animation->frames[animation->currFrameIndex], xPos, yPos, flipX, flipY);
}

void Animation_PlayState(Animation* animation, int state) {
	animation->isPlaying = state;
}


void Animation_Reset(Animation* animation) {
	if (animation->isPlaying) return;					//To prevent animation from restarting animation if already playing
	animation->played = 0;
	if (animation->currFrameIndex == 0) return;
	animation->currFrameIndex = 0;
}

void Animation_SetFrame(Animation* animation, int index) {
	animation->currFrameIndex = index;
}