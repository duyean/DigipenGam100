#pragma once

#include "../../CMP_Sprite_Pak.h"

typedef struct {
	float currentPositionX;
	float currentPositionY;
	int isMoving, isInteracting;
	int faceDirection;
	//Extra that Edmund suggest to add something like this
	int playerHealth;
}Player;

//Extra that Edmund suggest to add something like this
//are we importing bool.h?
int KillPlayer(Player* player);

void InitPlayer(Player *player);
void PlayerUpdate(Player *player);
Spritesheet GetPlayerSheet(void);
