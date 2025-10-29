#pragma once

typedef struct {
	float x, y, w, h;
	int a;
	char* text;
	float textOffsetX, textOffsetY;
	void (*OnButtonPress)(void);
}Button;