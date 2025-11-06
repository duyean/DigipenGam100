#pragma once

typedef struct {
	Spritesheet sheet;
	SpriteData* frames;
	int noOfSprites;
	int currFrameIndex;
	int toLoop;
	int played;
	int isPlaying;
	float frameDuration;
	float lastFrameTime;
} Animation;