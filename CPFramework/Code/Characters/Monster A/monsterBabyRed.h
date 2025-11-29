/*---------------------------------------------------------------
  File: monsterBabyRed.h
  Project: GAM100, Team ChocoMochiPie
  Author: Edmund
  Purpose: Monster controller for ramping variant

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once
#ifndef _monster_Baby_Red_
#define _monster_Baby_Red_
#include "monsterBase.h"

// WORK IN PROGRESS DO NOT REFACTOR

typedef enum RED_BABY_AI_STATE
{
	RED_STATE_IDLE,
	RED_STATE_PATROL,
	RED_STATE_ALERT,
	RED_STATE_CHASE,
	RED_STATE_ATTACK,
	RED_STATE_LOST,
	RED_STATE_DIGEST,
	RED_STATE_ERROR,
} RED_BABY_AI_STATE;

typedef struct MonsterRedBabyObject
{
	MonsterObject itself;
	RED_BABY_AI_STATE current_state;
	CP_Image monsterSheetImage[5];
	Spritesheet monsterSheet[5];
}MonsterRedBabyObject;


MonsterRedBabyObject* createRedBabyMonster(int x, int y, float movementSpeed, float detection, float attack, float lost);
void destroyRedBabyMonster(MonsterRedBabyObject* obj);
void InitializeRedBaby(void);
void clearRedBabyMonsterListMemory(void);
void externalCreateM_RB(int x, int y);
void sendRBMonstersToTrap(float trapXPos, float trapYPos);
void UpdateMonsterRedBaby();
void TeleportRBMonsterRoom(int amt, int check, int playerPos);
#endif
