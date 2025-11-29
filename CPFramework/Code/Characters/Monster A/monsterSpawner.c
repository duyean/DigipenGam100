/*---------------------------------------------------------------
  File: monsterSpawner.c
  Project: GAM100, Team ChocoMochiPie
  Author: Edmund
  Purpose: monster spawning mechanics

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "monsterSpawner.h"


void SpawnMonster(MONSTER_TYPE type, int amount, float minRange, float maxRange)
{
	for (int i = 0; i < amount; i++)
	{
		float xPos = CP_Random_RangeFloat(minRange, maxRange);
		if (xPos > -1600 && xPos < 1600)
		{
			if (xPos < 0)
			{
				xPos -= 1600;
			}
			else if (xPos > 0)
			{
				xPos += 1600;
			}
			
		}

		switch (type)
		{
		case BABY:
		{
			//default 0 here until further notice
			externalCreateM_B((int)xPos, 0);
				break;
		}
		case RED_BABY:
		{
			//Speed up when chasing
			externalCreateM_RB((int)xPos,0);
			break;
		}
		case CHAINS:
		{
			//Freezes for set amount of seconds if you look at it, very fast
			break;
		}
		}
	}
	
}

void ClearAllMonster(void)
{
	Monsters_Unload();
	clearRedBabyMonsterListMemory();
	//clear everything
}