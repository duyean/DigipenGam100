#pragma once

#include "utils.h"

typedef struct {
	float currentPositionX;
	float currentPositionY;
	int isMoving, isInteracting;
	int faceDirection;
}Player;

void InitPlayer(Player *player);
void PlayerUpdate(Player *player);
Spritesheet GetPlayerSheet(void);
