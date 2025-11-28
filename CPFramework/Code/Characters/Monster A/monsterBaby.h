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
	STATE_DIGEST,
	STATE_ERROR,
} BABY_AI_STATE;

typedef struct MonsterBabyObject
{
	MonsterObject itself;
	BABY_AI_STATE current_state;
	CP_Image monsterSheetImage[5];
	Spritesheet monsterSheet[5];
}MonsterBabyObject;


MonsterBabyObject* createBabyMonster(int x, int y, float movementSpeed, float detection, float attack, float lost);
void destroyBabyMonster(MonsterBabyObject* obj);
void InitializeBaby(void);
void Monsters_Unload(void);
void externalCreateM_B(int x, int y);
void sendMonstersToTrap(float trapXPos, float trapYPos);
void UpdateMonsterBaby();
void TeleportMonsterRoom(int amt, int check, int playerPos);
#endif
