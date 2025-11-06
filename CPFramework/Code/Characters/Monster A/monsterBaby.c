#include "monsterBaby.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 
#define ArraySize(a) (sizeof(a)/sizeof(a[0]))

// WORK IN PROGRESS DO NOT REFACTOR

List* babyList;
Player* playerRef;
CP_Vector *trapTriggeredPos;
TextTemplate babyTextTemplate;

void setPlayerRef(Player *player)
{
	playerRef = player;
}

MonsterBabyObject* createBabyMonster(int x, int y, float movementSpeed, float detection, float attack, float lost)
{
	MonsterBabyObject* new = (MonsterBabyObject*)malloc(sizeof(MonsterBabyObject));
	if (!new)
	{
		return NULL;
	}
	//ADD STUFF

	int rowFrames[4] = { 0,1,0,1 };
	int columnFrames[4] = { 0,0,1,1 };
	float frameDuration = 15.f;


	new->itself.transform.x = x;
	new->itself.transform.y = y;
	new->itself.movementSpeed = movementSpeed;//15.f;
	new->itself.detectionRange = detection;//200.f;
	new->itself.attackRange = attack;//10.f;
	new->itself.lostTimer = lost; //15.f;
	new->itself.lostTimerOriginal = lost;
	new->itself.randTimerCheck = 5.f;
	new->itself.randTimerCheckOriginal = 5.f;
	new->itself.facingDir = 1;
	new->current_state = STATE_IDLE;
	new->itself.isActive = true;
	new->itself.monsterSheetImage = CP_Image_Load("./Assets/WalkCycleSpriteSheet.png");
	new->itself.monsterSheet = CreateSpritesheet(new->itself.monsterSheetImage, 258, 258);
	new->itself.monsterAnimation = CreateAnimation(new->itself.monsterSheet, columnFrames, rowFrames, frameDuration,
		ArraySize(columnFrames), ArraySize(rowFrames));
	return new;

}

void destroyBabyMonster(MonsterBabyObject* obj)
{
	if (obj) {
		free(obj);
	}
}

void clearBabyMonsterListMemory(void)
{
	for (int i = 0; i < babyList->size; i++)
	{
		MonsterBabyObject* obj = (MonsterBabyObject*)listGet(babyList, i);
		destroyBabyMonster(obj);
	}
	listDestroy(babyList);
}
void initializeBaby(void)
{
	babyList = listCreate(5);
	listAdd(babyList, createBabyMonster(500, 500, 15.f, 400.f, 10.f, 5.f));
	babyTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));

	CP_Font_Set(babyTextTemplate.font);
}

void sendMonstersToTrap(float trapXPos, float trapYPos)
{
	*trapTriggeredPos = CP_Vector_Set(trapXPos, trapYPos);
}

void processing_state_babyFSM(BABY_AI_STATE *current_state, BABY_AI_STATE nextState)
{
	//Event == 0 no changes to event

	switch (*current_state)
	{
	case STATE_IDLE:
	{
		if (nextState == STATE_PATROL) //Nothing to do, go patrol
		{
			*current_state = STATE_PATROL;
		}
		else if (nextState == STATE_ALERT) //Alerted
		{
			*current_state = STATE_ALERT;
		}
		break;
	}
	case STATE_PATROL:
	{
		if (nextState == STATE_IDLE) //Finish Moving
		{
			*current_state = STATE_IDLE;
		}
		else if (nextState == STATE_ALERT) //Alerted
		{
			*current_state = STATE_ALERT;
		}
		break;
	}
	case STATE_ALERT:
	{
		if (nextState == STATE_IDLE) //Finish Player not found
		{
			*current_state = STATE_IDLE;
		}
		else if (nextState == STATE_CHASE) //Player Found
		{
			*current_state = STATE_CHASE;
		}
		else if (nextState == STATE_LOST) //Player Found
		{
			*current_state = STATE_LOST;
		}
		break;
	}
	case STATE_CHASE:
	{
		if (nextState == STATE_LOST) //Lost player
		{
			*current_state = STATE_LOST;
		}
		else if (nextState == STATE_ATTACK) //Player reached
		{
			*current_state = STATE_ATTACK;
		}
		break;
	}
	case STATE_ATTACK:
	{
		if (nextState == STATE_IDLE) //player dead
		{
			*current_state = STATE_IDLE;
		}
		else if (nextState == STATE_CHASE) //Player Running
		{
			*current_state = STATE_CHASE;
		}
		break;
	}
	case STATE_LOST:
	{
		if (nextState == STATE_IDLE) //Go back to idling
		{
			*current_state = STATE_IDLE;
		}
		break;
	}
	}
}

void processing_state_baby_logic(MonsterBabyObject *baby)
{

	CP_Vector dir = CP_Vector_Set(playerRef->currentPositionX - baby->itself.transform.x, playerRef->currentPositionY - baby->itself.transform.y);
	CP_Vector normDir = CP_Vector_Normalize(dir);
	int distFromPlayer = CP_Vector_Length(dir);

	if (baby->itself.randTimerCheck > 0.f)
	{
		baby->itself.randTimerCheck -= CP_System_GetDt();
	}

	//Do AI Logic
	switch (baby->current_state)
	{
	case STATE_IDLE:
	{
		//check facing direction, play idle animation
		//Monster facing and player is same direction
		if (baby->itself.facingDir > 0 && normDir.x > 0 || baby->itself.facingDir < 0 && normDir.x < 0)
		{
			if (distFromPlayer < baby->itself.detectionRange) //Check if in range
			{
				//start alerted state
				processing_state_babyFSM(&baby->current_state, STATE_ALERT);

			}
		}

		if (baby->itself.randTimerCheck <= 0.f)
		{
			if (CP_Random_RangeInt(0, 100) < 10) //10% chance to patrol each frame
			{

				if (CP_Random_RangeInt(0, 100) < 50) //50/50 for direction;
				{
					baby->itself.facingDir = 1;
				}
				else
				{
					baby->itself.facingDir = -1;
				}
				processing_state_babyFSM(&baby->current_state, STATE_PATROL);
			}
			baby->itself.randTimerCheck = baby->itself.randTimerCheckOriginal;
		}
		break;
	}
	case STATE_PATROL:
	{
		//Monster facing and player is same direction
		if (baby->itself.facingDir > 0 && normDir.x > 0 || baby->itself.facingDir < 0 && normDir.x < 0)
		{
			if (distFromPlayer < baby->itself.detectionRange) //Check if in range
			{
				//start alerted state
				processing_state_babyFSM(&baby->current_state, STATE_ALERT);

			}
		}
		//Monster facing and player is same direction
	
		if (distFromPlayer < baby->itself.detectionRange / 2.f) //Check if player too close
		{
			//start alerted state
			processing_state_babyFSM(&baby->current_state, STATE_ALERT);

		}



		if (baby->itself.randTimerCheck <= 0.f)
		{
			if (CP_Random_RangeInt(0, 100) < 50) //50% chance to go back to idle each frame;
			{
				baby->itself.transform.x += baby->itself.facingDir * (baby->itself.movementSpeed * CP_System_GetDt());
			}
			baby->itself.randTimerCheck = baby->itself.randTimerCheckOriginal;
		}
		break;
	}
	case STATE_ALERT:
	{
		if (distFromPlayer <= baby->itself.detectionRange) //Check if in range
		{
			//start alerted state
			processing_state_babyFSM(&baby->current_state, STATE_CHASE);

		}
		else
		{
			if (baby->itself.randTimerCheck <= 0.f)
			{
				if (CP_Random_RangeInt(0, 100) < 5) //5% chance it gets bored and goes back to idling
				{
					processing_state_babyFSM(&baby->current_state, STATE_IDLE);
				}
				baby->itself.randTimerCheck = baby->itself.randTimerCheckOriginal;
			}

			//walk towards trap triggered location -todo
			CP_Vector trapDir = CP_Vector_Set(trapTriggeredPos->x - baby->itself.transform.x, trapTriggeredPos->y - baby->itself.transform.y);
			CP_Vector trapNorm = CP_Vector_Normalize(trapDir);
			int distFromTrap = CP_Vector_Length(trapDir);
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
				processing_state_babyFSM(&baby->current_state, STATE_LOST); //player not found
			}

		}
		break;
	}
	case STATE_CHASE:
	{
		//Check if left or right and same floor
		if (distFromPlayer < baby->itself.attackRange)
		{
			processing_state_babyFSM(&baby->current_state, STATE_ATTACK);
		}
		//If player disappears into a hiding place or gets too far
		// add LOST STATE transition here
		if (distFromPlayer > baby->itself.detectionRange * 1.5f)
		{
			processing_state_babyFSM(&baby->current_state, STATE_LOST);
		}
		//Go left towards player
		if (normDir.x > 0)
		{
			baby->itself.facingDir = 1;
		}
		else //Go right towards player
		{
			baby->itself.facingDir = -1;
		}
		baby->itself.transform.x += baby->itself.facingDir * (baby->itself.movementSpeed * CP_System_GetDt());
		break;
	}
	case STATE_ATTACK:
	{
		//Kill player & play animation ? are we doing collision check here or guaranteed kill when reach this
		KillPlayer(playerRef);
		processing_state_babyFSM(&baby->current_state, STATE_IDLE);
		break;
	}
	case STATE_LOST:
	{
	    //Idle, play lost animation
		if (baby->itself.lostTimer <= 0.f)
		{
			baby->itself.lostTimer = baby->itself.lostTimerOriginal;
			processing_state_babyFSM(&baby->current_state, STATE_IDLE);
		}
		else
		{
			baby->itself.lostTimer -= CP_System_GetDt();
		}
		break;
	}
	}
}

const char* intToConstChar(int num) {
	int len = snprintf(NULL, 0, "%d", num);
	char* str = (char*)malloc(len + 1);
	if (str == NULL) {
		perror("Failed to allocate memory for string");
		return NULL;
	}
	snprintf(str, len + 1, "%d", num);

	return str;
}

void UpdateMonsterBaby()
{
	for (int i = 0; i < babyList->size; i++)
	{
		MonsterBabyObject* obj = (MonsterBabyObject*)listGet(babyList, i);
		if (obj->itself.isActive == false)
		{
			continue;
		}
		processing_state_baby_logic(obj);
		//Animate(&obj->itself.monsterAnimation, obj->itself.transform.x, 450);
		DrawSprite(obj->itself.monsterSheet, 1, 0, obj->itself.transform.x, obj->itself.transform.y, 1, 1);
		CP_Font_DrawText(intToConstChar((int)obj->current_state), obj->itself.transform.x, obj->itself.transform.y - 100.f);
	}
}
