#pragma once

#include "../../CMP_Sprite_Pak.h"

typedef struct {
	float currentPositionX;
	float currentPositionY;
	int isMoving, isInteracting;
	int faceDirection;
}Player;

void InitPlayer(Player *player);
void PlayerUpdate(Player *player);
Spritesheet GetPlayerSheet(void);
