/*---------------------------------------------------------------
  File: monsterBabyRed.c
  Project: GAM100, Team ChocoMochiPie
  Author: Edmund
  Purpose: Monster controller for ramping variant

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "monsterBabyRed.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h> 
#include "../../Rewrites/ListFile.h"
#define ArraySize(a) (sizeof(a)/sizeof(a[0]))
#define OriginalSpeed 210.f

// WORK IN PROGRESS DO NOT REFACTOR

List* RedbabyList;
CP_Vector trapTriggeredPos;

SpriteData monsterSprites[5][4];
Animation AnimationList[5];


CP_Sound monsterSfx[3];

MonsterRedBabyObject* createRedBabyMonster(int x, int y, float movementSpeed, float detection, float attack, float lost)
{
	MonsterRedBabyObject* new = (MonsterRedBabyObject*)malloc(sizeof(MonsterRedBabyObject));
	if (!new)
	{
		return NULL;
	}
	//ADD STUFF

	int rowFrames[4] = { 0,1,0,1 };
	int columnFrames[4] = { 0,0,1,1 };
	float frameDuration = 15.f;

	new->itself.transform.x = (float)x;
	new->itself.transform.y = (float)y;
	new->itself.movementSpeed = movementSpeed;//15.f;
	new->itself.detectionRange = detection;//200.f;
	new->itself.attackRange = attack;//10.f;
	new->itself.lostTimer = lost; //15.f;
	new->itself.lostTimerOriginal = lost;
	new->itself.moveTimer = 4.f;
	new->itself.moveTimerOriginal = 4.f;
	new->itself.randTimerCheck = 2.f;
	new->itself.randTimerCheckOriginal = 5.f;
	new->itself.facingDir = -1;
	new->current_state = RED_STATE_IDLE;
	new->itself.isActive = true;
	new->monsterSheetImage[0] = CP_Image_Load("./Assets/IdleSpriteSheet.png");
	new->monsterSheetImage[1] = CP_Image_Load("./Assets/MoveSpriteSheet.png");
	new->monsterSheetImage[2] = CP_Image_Load("./Assets/ChaseSpriteSheet.png");
	new->monsterSheetImage[3] = CP_Image_Load("./Assets/EatSpriteSheet.png");
	new->monsterSheetImage[4] = CP_Image_Load("./Assets/DigestSpriteSheet.png");


	for (int p = 0; p < 5; p++)
	{
		int characterSpriteDimension = CP_Image_GetWidth(new->monsterSheetImage[p]) / 2;
		int currentIndex = 0;
		for (int i = 0; i < 4 / 2; i++) {
			for (int j = 0; j < 4 / 2; j++) {
				monsterSprites[p][currentIndex] = SpriteData_Create(characterSpriteDimension, characterSpriteDimension, j, i, 255.f);
				currentIndex++;
			}
		}
		new->monsterSheet[p] = Spritesheet_Create(new->monsterSheetImage[p], 258, 258);
		if (p == 3)
		{
			AnimationList[p] = Animation_Create(new->monsterSheet[p], monsterSprites[p], frameDuration, 4, 0, 1);
		}
		else
		{
			AnimationList[p] = Animation_Create(new->monsterSheet[p], monsterSprites[p], frameDuration, 4, 1, 1);
		}
	
	}

	new->itself.monsterAnimation = AnimationList[0];
	return new;

}

void destroyRedBabyMonster(MonsterRedBabyObject* obj)
{
	if (obj) {
		free(obj);
	}
}

void clearRedBabyMonsterListMemory(void)
{
	if (RedbabyList != NULL)
	{
		for (int i = RedbabyList->size - 1; i >= 0; i--)
		{
			MonsterRedBabyObject* obj = (MonsterRedBabyObject*)(intptr_t)ListGet(RedbabyList, i);
			ListRemoveAt(RedbabyList, i);
			destroyRedBabyMonster(obj);
		}

		ListDestroy(RedbabyList);
	}
	for (int i = 0; i < 3; i++) {
		CP_Sound_Free(monsterSfx[i]);
	}
}
void InitializeRedBaby(void)
{
	monsterSfx[0] = CP_Sound_Load("./Assets/Audio/Cry1.wav");
	monsterSfx[1] = CP_Sound_Load("./Assets/Audio/Cry2.wav");
	monsterSfx[2] = CP_Sound_Load("./Assets/Audio/Cry3.wav");

	RedbabyList = ListCreate(10);

	trapTriggeredPos = CP_Vector_Set(0, 0);

}

void externalCreateM_RB(int x, int y)
{
	//default y=0;
	ListAppend(RedbabyList, createRedBabyMonster(x, y, OriginalSpeed, 500.f, 50.f, 5.f));
}


void sendRBMonstersToTrap(float trapXPos, float trapYPos)
{
	trapTriggeredPos = CP_Vector_Set(trapXPos, trapYPos);
}

void processing_state_RedbabyFSM(RED_BABY_AI_STATE* current_state, RED_BABY_AI_STATE nextState, MonsterRedBabyObject* baby)
{
	CP_Vector dir = CP_Vector_Set(playerRef->currentPositionX - baby->itself.transform.x, playerRef->currentPositionY - baby->itself.transform.y);
	int distFromPlayer = (int)CP_Vector_Length(dir);

	Animation_Reset(&baby->itself.monsterAnimation);
	switch (*current_state)
	{
	case RED_STATE_IDLE:
	{
		
		if (nextState == RED_STATE_PATROL) //Nothing to do, go patrol
		{
			baby->itself.monsterAnimation = AnimationList[1];
			*current_state = RED_STATE_PATROL;
		}
		else if (nextState == RED_STATE_ALERT) //Alerted
		{
			baby->itself.monsterAnimation = AnimationList[1];
			*current_state = RED_STATE_ALERT;
		}
		break;
	}
	case RED_STATE_PATROL:
	{
		//CP_Sound_PlayAdvanced(monsterSfx[CP_Random_RangeInt(0, 2)], changeRange(distFromPlayer, 0.f, 1.f, 0.f, (baby->itself.detectionRange * 2)), CP_Random_RangeFloat(0.f, 0.8f), FALSE, CP_SOUND_GROUP_SFX);
		if (nextState == RED_STATE_IDLE) //Finish Moving
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = RED_STATE_IDLE;
		}
		else if (nextState == RED_STATE_ALERT) //Alerted
		{
			baby->itself.monsterAnimation = AnimationList[1];
			*current_state = RED_STATE_ALERT;
		}
		break;
	}
	case RED_STATE_ALERT:
	{
		//JELLY HERE
		CP_Sound_PlayAdvanced(monsterSfx[CP_Random_RangeInt(0, 2)], changeRange(distFromPlayer, 0.f, 0.8f, 0.1f, (baby->itself.detectionRange * 2)), CP_Random_RangeFloat(0.f, 0.8f), FALSE, CP_SOUND_GROUP_0);
		if (nextState == RED_STATE_IDLE) //Finish Player not found
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = RED_STATE_IDLE;
		}
		else if (nextState == RED_STATE_CHASE) //Player Found
		{
			baby->itself.monsterAnimation = AnimationList[2];
			*current_state = RED_STATE_CHASE;
		}
		else if (nextState == RED_STATE_LOST) //Player lost
		{
			*current_state = RED_STATE_LOST;
		}
		break;
	}
	case RED_STATE_CHASE:
	{
		//testing
	
		if (nextState == RED_STATE_LOST) //Lost player
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = RED_STATE_LOST;
		}
		else if (nextState == RED_STATE_ATTACK) //Player reached
		{
			baby->itself.monsterAnimation = AnimationList[3];
			*current_state = RED_STATE_ATTACK;
		}
		break;
	}
	case RED_STATE_ATTACK:
	{
		if (nextState == RED_STATE_IDLE) //player dead
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = RED_STATE_IDLE;
		}
		else if (nextState == RED_STATE_CHASE) //Player Running
		{
			baby->itself.monsterAnimation = AnimationList[2];
			*current_state = RED_STATE_CHASE;
		}
		else if (nextState == RED_STATE_DIGEST) //Player eaten
		{
			baby->itself.monsterAnimation = AnimationList[4];
			*current_state = RED_STATE_DIGEST;
		}
		break;
	}
	case RED_STATE_LOST:
	{

		if (nextState == RED_STATE_IDLE) //Go back to idling
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = RED_STATE_IDLE;
		}
		else if (nextState == RED_STATE_CHASE) //Go back to chasing if found
		{
			baby->itself.monsterAnimation = AnimationList[2];
			*current_state = RED_STATE_CHASE;
		}
		break;
	}
	case RED_STATE_DIGEST:
	{
		if (nextState == RED_STATE_IDLE) //Go back to idling
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = RED_STATE_IDLE;
		}
		break;
	}
	}
}

void processing_state_Redbaby_logic(MonsterRedBabyObject* baby)
{

	CP_Vector dir = CP_Vector_Set(playerRef->currentPositionX - baby->itself.transform.x, playerRef->currentPositionY - baby->itself.transform.y);
	CP_Vector normDir = CP_Vector_Normalize(dir);
	int distFromPlayer = (int)CP_Vector_Length(dir);


	

	if (baby->itself.randTimerCheck > 0.f)
	{
		baby->itself.randTimerCheck -= CP_System_GetDt(); 
	}

	//Do AI Logic
	switch (baby->current_state)
	{
	case RED_STATE_IDLE:
	{
		//check facing direction, play idle animation
		//Monster facing and player is same direction
		
		if (baby->itself.facingDir > 0 && normDir.x > 0 || baby->itself.facingDir < 0 && normDir.x < 0)
		{
			if (distFromPlayer < baby->itself.detectionRange && playerRef->isHiding == 0) //Check if in range
			{
				//start alerted state
				processing_state_RedbabyFSM(&baby->current_state, RED_STATE_ALERT, baby);

			}
		}
		if (distFromPlayer < baby->itself.detectionRange / 1.5f && playerRef->isHiding == 0) //Check if player too close
		{
			//start alerted state

			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_ALERT, baby);

		}

		if (baby->itself.randTimerCheck <= 0.f)
		{
			if (CP_Random_RangeInt(0, 100) < 80) //80% chance to patrol each frame
			{

				if (CP_Random_RangeInt(0, 100) < 50) //50/50 for direction;
				{
					baby->itself.facingDir = 1;
				}
				else
				{
					baby->itself.facingDir = -1;
				}
				processing_state_RedbabyFSM(&baby->current_state, RED_STATE_PATROL, baby);
			}
			baby->itself.randTimerCheck = baby->itself.randTimerCheckOriginal;
		}
		break;
	}
	case RED_STATE_PATROL:
	{
		//Monster facing and player is facing each other
		if (baby->itself.facingDir > 0 && normDir.x > 0 || baby->itself.facingDir < 0 && normDir.x < 0)
		{
			if (distFromPlayer < baby->itself.detectionRange && playerRef->isHiding == 0 && playerRef->toDraw == 1) //Check if in range
			{
				//start alerted state

				processing_state_RedbabyFSM(&baby->current_state, RED_STATE_ALERT, baby);

			}
		}

		if (distFromPlayer < baby->itself.detectionRange / 1.5f && playerRef->isHiding == 0 && playerRef->toDraw == 1) //Check if player too close
		{
			//start alerted state

			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_ALERT, baby);

		}


		baby->itself.transform.x += baby->itself.facingDir * (baby->itself.movementSpeed * CP_System_GetDt());

		if (baby->itself.randTimerCheck <= 0.f)
		{
			if (CP_Random_RangeInt(0, 100) < 60) //50% chance to go back to idle each frame;
			{
				processing_state_RedbabyFSM(&baby->current_state, RED_STATE_IDLE, baby);
			}
		
			baby->itself.randTimerCheck = baby->itself.randTimerCheckOriginal;
		}
		break;
	}
	case RED_STATE_ALERT:
	{
;
		if (distFromPlayer <= baby->itself.detectionRange && playerRef->isHiding == 0) //Check if in range
		{
			//start alerted state
			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_CHASE, baby);

		}
		else
		{
			if (baby->itself.randTimerCheck <= 0.f)
			{
				if (CP_Random_RangeInt(0, 100) < 5) //5% chance it gets bored and goes back to idling
				{
					processing_state_RedbabyFSM(&baby->current_state, RED_STATE_IDLE, baby);
				}
				baby->itself.randTimerCheck = baby->itself.randTimerCheckOriginal;
			}

			//walk towards trap triggered location -todo
			CP_Vector trapDir = CP_Vector_Set(trapTriggeredPos.x - baby->itself.transform.x, trapTriggeredPos.y - baby->itself.transform.y);
			CP_Vector trapNorm = CP_Vector_Normalize(trapDir);
			int distFromTrap = (int)CP_Vector_Length(trapDir);
			if (distFromTrap > 5.f)
			{


				if (trapNorm.x > 0)
				{
					baby->itself.facingDir = 1;
				}
				else //Go right towards trap
				{
					baby->itself.facingDir = -1;
				}
				baby->itself.transform.x += baby->itself.facingDir * (baby->itself.movementSpeed * CP_System_GetDt());
			}
			else
			{

				processing_state_RedbabyFSM(&baby->current_state, RED_STATE_LOST, baby); //player not found
			}

		}
		break;
	}
	case RED_STATE_CHASE:
	{
		//Check if left or right and same floor
		if (distFromPlayer < baby->itself.attackRange && playerRef->isHiding == 0)
		{
			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_ATTACK, baby);
		}
		//If player disappears into a hiding place or gets too far
		// add LOST STATE transition here
		if (distFromPlayer > baby->itself.detectionRange * 1.5f)
		{
			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_LOST, baby);
			baby->itself.moveTimer = baby->itself.moveTimerOriginal;
		}
		else if (playerRef->isHiding == 1 && baby->itself.moveTimer <= 0.f)
		{
			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_LOST, baby);
			baby->itself.moveTimer = baby->itself.moveTimerOriginal;
		}
		else if (playerRef->isHiding == 1 && baby->itself.moveTimer > 0.f)
		{
			baby->itself.moveTimer -= CP_System_GetDt();
		}

		if (playerRef->isHiding == 0)
		{
			//Go left towards player
			if (normDir.x > 0)
			{
				baby->itself.facingDir = 1;
			}
			else //Go right towards player
			{
				baby->itself.facingDir = -1;
			}
			baby->itself.moveTimer = baby->itself.moveTimerOriginal;
		}

		
		
		baby->itself.movementSpeed += 10.f * DeltaTime();
		baby->itself.transform.x += baby->itself.facingDir * (baby->itself.movementSpeed * CP_System_GetDt());
		break;
	}
	case RED_STATE_ATTACK:
	{
		baby->itself.movementSpeed = OriginalSpeed;
		//Kill player & play animation ? are we doing collision check here or guaranteed kill when reach this
		if (baby->itself.monsterAnimation.currFrameIndex == 2)
		{
			playerRef->toDraw = 0;
			playerRef->currentHealth = 0;
		}
		if (baby->itself.monsterAnimation.currFrameIndex == 3)
		{
			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_DIGEST, baby);
		}
		break;
	}
	case RED_STATE_DIGEST:
	{
		//Idle, play lost animation
		//End game
		break;
	}
	case RED_STATE_LOST:
	{
		baby->itself.movementSpeed = OriginalSpeed;
		//Idle, play lost animation
		if (baby->itself.lostTimer <= 0.f)
		{
			baby->itself.lostTimer = baby->itself.lostTimerOriginal;
			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_IDLE, baby);
		}
		else if(distFromPlayer < baby->itself.detectionRange && playerRef->isHiding == 0)
		{
			baby->itself.lostTimer = baby->itself.lostTimerOriginal;
			processing_state_RedbabyFSM(&baby->current_state, RED_STATE_CHASE, baby);
		}
		else
		{
			baby->itself.lostTimer -= CP_System_GetDt();
		}
		break;
	}
	}
}

void UpdateMonsterRedBaby()
{
	for (int i = 0; i < RedbabyList->size; i++)
	{
		MonsterRedBabyObject* obj = (MonsterRedBabyObject*)ListGet(RedbabyList, i);
		if (obj != NULL)
		{
			if (obj->itself.isActive == false)
			{
				continue;
			}
			processing_state_Redbaby_logic(obj);

			CP_Settings_Tint(CP_Color_Create(255, 0, 0, 180));
			Animation_Animate(&obj->itself.monsterAnimation, (obj->itself.transform.x - playerRef->currentPositionX), (obj->itself.transform.y - playerRef->currentPositionY), obj->itself.facingDir * -1, 1);
			CP_Settings_Tint(CP_Color_Create(0, 0, 0, 0));

			if (playerRef->isDebugMode == 1)
			{
				char buffer[300];
				snprintf(buffer, sizeof(buffer), "STATE: %d", (int)obj->current_state);
				CP_Font_DrawText(buffer, (obj->itself.transform.x - playerRef->currentPositionX) + 750, CP_System_GetWindowHeight() / 2 - 150);
			}
		}
	}
}

void TeleportRBMonsterRoom(int amt, int check, int playerPos)
{
	for (int i = 0; i < RedbabyList->size; i++)
	{
		MonsterRedBabyObject* obj = (MonsterRedBabyObject*)ListGet(RedbabyList, i);
		if (obj != NULL)
		{
			if (obj->itself.isActive == false)
			{
				continue;
			}
			if (obj->current_state == RED_STATE_CHASE && check == 1)
			{
				obj->itself.transform.x += amt;
			}
			else if (obj->current_state == RED_STATE_PATROL && check == 1)
			{
				if ((obj->itself.transform.x < 3600 && obj->itself.transform.x > 2000) && playerPos != 2)				//between 3600 and 2000 monster is in the right room
				{
					obj->itself.transform.x = !obj->itself.transform.x;
				}
				else if ((obj->itself.transform.x > -3600 && obj->itself.transform.x < -2000) && playerPos != -2) 			//between -3600 and -2000 monster is in left room
				{
					obj->itself.transform.x = !obj->itself.transform.x;
				}
			}
			else if (check == 0)
			{


				if ((obj->itself.transform.x < 3600 && obj->itself.transform.x > 2000) && playerPos != 2)				//between 3600 and 2000 monster is in the right room
				{
					obj->itself.transform.x = !obj->itself.transform.x;
				}
				else if ((obj->itself.transform.x > -3600 && obj->itself.transform.x < -2000) && playerPos != -2) 			//between -3600 and -2000 monster is in left room
				{
					obj->itself.transform.x = !obj->itself.transform.x;
				}
			}

		}
	}
}
