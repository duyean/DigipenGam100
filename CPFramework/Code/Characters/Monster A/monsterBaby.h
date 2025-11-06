#pragma once
#ifndef _monster_Baby_
#define _monster_Baby_
#include "monsterBase.h"

// WORK IN PROGRESS DO NOT REFACTOR

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


MonsterBabyObject* createBabyMonster(int x, int y, float movementSpeed, float detection, float attack, float lost);
void destroyBabyMonster(MonsterBabyObject* obj);
void setPlayerRef(Player* player);
void initializeBaby(void);
void sendMonstersToTrap(float trapXPos, float trapYPos);
void UpdateMonsterBaby();
#endif
