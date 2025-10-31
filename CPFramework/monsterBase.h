#pragma once
#ifndef _monster_Base_
#define _monster_Base_

#include "cprocessing.h"
#include "utils.h"
#include <stdbool.h>

// WORK IN PROGRESS DO NOT REFACTOR

typedef struct MonsterObject
{
	CP_Vector transform;
	bool isActive;
	CP_Image monsterSheetImage;
	Spritesheet monsterSheet;
	Animation monsterAnimation;
	int rowFrames[4];
	int patrolMaxLength;
	int columnFrames[4];
	float frameDuration;
	float movementSpeed;

} MonsterObject;

#endif
