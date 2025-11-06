#pragma once
#ifndef _monster_Base_
#define _monster_Base_

#include "cprocessing.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Sprite_Pak.h"
#include "../../CMP_Player_Pak.h"
#include "../../CMP_Text_Pak.h"
#include <stdbool.h>

// WORK IN PROGRESS DO NOT REFACTOR

typedef struct MonsterObject
{
	CP_Vector transform;
	bool isActive;
	float detectionRange;
	float attackRange;
	float lostTimer;
	float lostTimerOriginal;
	int facingDir;
	float randTimerCheck;
	float randTimerCheckOriginal;
	CP_Image monsterSheetImage;
	Spritesheet monsterSheet;
	Animation monsterAnimation;
	int rowFrames[4];
	int columnFrames[4];
	float frameDuration;
	float movementSpeed;

} MonsterObject;

#endif
