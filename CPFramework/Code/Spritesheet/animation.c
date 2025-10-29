#include "../CMP_Core_Pak.h"
#include "spriteClass.h"
#include "animateClass.h"
#include "spritesheet.h"
#include <stdio.h>

/*
*
* Uses Init 'Spritesheet', the array format of each frame in order, the time between frames, and size each dimension
* Return: Initialized Animation
* Uses : To Create references to animation
* Sub - uses : NIL
*/
Animation CreateAnimation(Spritesheet sheet, int cFrames[10], int rFrames[10], float animationSpeed, int cSize, int rSize) {
	Animation newAnimation;
	newAnimation.frameDuration = animationSpeed;
	newAnimation.columnFrames = cFrames;
	newAnimation.rowFrames = rFrames;
	newAnimation.currentColumnFrame = 0;
	newAnimation.currentRowFrame = 0;
	newAnimation.columnSize = cSize;
	newAnimation.rowSize = rSize;
	newAnimation.sheet = sheet;
	return newAnimation;
}

/*
* Animate takes in a 'Animation' Pointer as a source, the x and y position of the animation and the elapsedTime of the game
* Returns: NIL
* Uses: To Animate the passed in animation of whatever game object
* Sub-uses: NIL
*/
void Animate(Animation* animation, float x, float y, int flipX, int flipY) {
	float currentTime = ElapsedTimeSeconds();
	if (animation->lastFrameTime <= currentTime) {
		animation->lastFrameTime = currentTime + animation->frameDuration * DeltaTime();

		animation->currentColumnFrame++;
		animation->currentRowFrame++;

		if (animation->currentRowFrame >= animation->rowSize) {
			animation->currentRowFrame = 0;
		}
		if (animation->currentColumnFrame >= animation->columnSize) {
			animation->currentColumnFrame = 0;
		}
	}

	int rowFrame = animation->rowFrames[animation->currentRowFrame];
	int columnFrame = animation->columnFrames[animation->currentColumnFrame];

	DrawSprite(animation->sheet, rowFrame, columnFrame, x, y, flipX, flipY);
}