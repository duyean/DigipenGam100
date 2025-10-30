#pragma once
#ifndef _monster_Baby_
#define _monster_Baby_
#include "monsterBase.h"

typedef enum BABY_AI_STATE
{
	STATE_IDLE,
	STATE_PATROL,
	STATE_ALERT,
	STATE_CHASE,
	STATE_ATTACK,
	STATE_LOST,
	STATE_ERROR,
} BABY_AI_STATE;

typedef struct MonsterBabyObject
{
	MonsterObject itself;
	BABY_AI_STATE current_state;
}MonsterBabyObject;

MonsterBabyObject* createBabyMonster(int x, int y, int patrolMax, float movementSpeed);
void destroyBabyMonster(MonsterBabyObject* obj);

#endif
