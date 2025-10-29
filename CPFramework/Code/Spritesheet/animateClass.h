#pragma once

typedef struct {
	Spritesheet sheet;
	int currentColumnFrame;
	int currentRowFrame;
	int columnSize;
	int rowSize;
	int *columnFrames;
	int *rowFrames;
	float frameDuration;
	float lastFrameTime;
} Animation;