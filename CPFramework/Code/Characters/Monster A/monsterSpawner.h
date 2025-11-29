/*---------------------------------------------------------------
  File: monsterSpawner.h
  Project: GAM100, Team ChocoMochiPie
  Author: Edmund
  Purpose: monster spawning mechanics

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once
#ifndef _monster_Spawner_
#define _monster_Spawner_

#include "cprocessing.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Sprite_Pak.h"
#include "../../CMP_Player_Pak.h"
#include "../../CMP_Text_Pak.h"
#include <stdbool.h>
#include "monsterBaby.h"
#include "monsterBabyRed.h"
#include "monsterBase.h"

typedef enum MONSTER_TYPE
{
	BABY,
	RED_BABY,
	CHAINS,
} MONSTER_TYPE;

//distanceApart if above max range it will spawn at /2 distance apart
void SpawnMonster(MONSTER_TYPE type, int amount, float minRange, float maxRange);

void ClearAllMonster(void);

#endif