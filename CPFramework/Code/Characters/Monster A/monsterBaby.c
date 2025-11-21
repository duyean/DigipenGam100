#include "monsterBaby.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 
#include "../../Rewrites/ListFile.h"
#define ArraySize(a) (sizeof(a)/sizeof(a[0]))

// WORK IN PROGRESS DO NOT REFACTOR

List* babyList;
CP_Vector trapTriggeredPos;
TextTemplate babyTextTemplate;

SpriteData monsterSprites[5][4];
Animation AnimationList[5];


CP_Sound monsterSfx[3];
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
	new->current_state = STATE_IDLE;
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

void destroyBabyMonster(MonsterBabyObject* obj)
{
	if (obj) {
		for (int i = 0; i < 5; i++) {
			CP_Image_Free(obj->monsterSheetImage[i]);
		}
		free(obj);
		
	}
}

void Monsters_Unload(void)
{
	if (babyList != NULL)
	{
		for (int i = 0; i < babyList->size; i++)
		{
			MonsterBabyObject* obj = (MonsterBabyObject*)ListGet(babyList, i);
			ListRemoveAt(babyList, i);
			destroyBabyMonster(obj);
		}

		ListDestroy(babyList);
	}
	for (int i = 0; i < 3; i++) {
		CP_Sound_Free(monsterSfx[i]);
	}
	CP_Font_Free(babyTextTemplate.font);
}


void InitializeBaby(void)
{
	monsterSfx[0] = CP_Sound_Load("./Assets/Audio/Cry1.wav");
	monsterSfx[1] = CP_Sound_Load("./Assets/Audio/Cry2.wav");
	monsterSfx[2] = CP_Sound_Load("./Assets/Audio/Cry3.wav");

	babyList = ListCreate(10);

	babyTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));

	CP_Font_Set(babyTextTemplate.font);
	trapTriggeredPos = CP_Vector_Set(0, 0);
;}

void externalCreateM_B(int x, int y)
{
	//default y=0;
	ListAppend(babyList, createBabyMonster(x, y, 110.f, 500.f, 50.f, 5.f));
}


void sendMonstersToTrap(float trapXPos, float trapYPos)
{
	trapTriggeredPos = CP_Vector_Set(trapXPos, trapYPos);
}

void processing_state_babyFSM(BABY_AI_STATE* current_state, BABY_AI_STATE nextState, MonsterBabyObject* baby)
{
	CP_Vector dir = CP_Vector_Set(playerRef->currentPositionX - baby->itself.transform.x, playerRef->currentPositionY - baby->itself.transform.y);
	int distFromPlayer = (int)CP_Vector_Length(dir);

	Animation_Reset(&baby->itself.monsterAnimation);
	switch (*current_state)
	{
	case STATE_IDLE:
	{
		
		if (nextState == STATE_PATROL) //Nothing to do, go patrol
		{
			baby->itself.monsterAnimation = AnimationList[1];
			*current_state = STATE_PATROL;
		}
		else if (nextState == STATE_ALERT) //Alerted
		{
			baby->itself.monsterAnimation = AnimationList[1];
			*current_state = STATE_ALERT;
		}
		break;
	}
	case STATE_PATROL:
	{
		//CP_Sound_PlayAdvanced(monsterSfx[CP_Random_RangeInt(0, 2)], changeRange((float)distFromPlayer, 0.f, 1.f, 0.f, (baby->itself.detectionRange * 2)), CP_Random_RangeFloat(0.f, 0.8f), FALSE, CP_SOUND_GROUP_SFX);
		if (nextState == STATE_IDLE) //Finish Moving
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = STATE_IDLE;
		}
		else if (nextState == STATE_ALERT) //Alerted
		{
			baby->itself.monsterAnimation = AnimationList[1];
			*current_state = STATE_ALERT;
		}
		break;
	}
	case STATE_ALERT:
	{
		//JELLY HERE
		//CP_Sound_PlayAdvanced(monsterSfx[CP_Random_RangeInt(0,2)], changeRange((float)distFromPlayer, 0.f, 0.6f, 0.f, (baby->itself.detectionRange * 2)), CP_Random_RangeFloat(0.f, 0.8f), FALSE, CP_SOUND_GROUP_SFX);
		if (nextState == STATE_IDLE) //Finish Player not found
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = STATE_IDLE;
		}
		else if (nextState == STATE_CHASE) //Player Found
		{
			baby->itself.monsterAnimation = AnimationList[2];
			*current_state = STATE_CHASE;
		}
		else if (nextState == STATE_LOST) //Player lost
		{
			*current_state = STATE_LOST;
		}
		break;
	}
	case STATE_CHASE:
	{
		CP_Sound_PlayAdvanced(monsterSfx[CP_Random_RangeInt(0, 2)], changeRange((float)distFromPlayer, 0.f, 0.6f, 0.f, (baby->itself.detectionRange * 2)), CP_Random_RangeFloat(0.f, 0.8f), FALSE, CP_SOUND_GROUP_SFX);
		if (nextState == STATE_LOST) //Lost player
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = STATE_LOST;
		}
		else if (nextState == STATE_ATTACK) //Player reached
		{
			baby->itself.monsterAnimation = AnimationList[3];
			*current_state = STATE_ATTACK;
		}
		break;
	}
	case STATE_ATTACK:
	{
		if (nextState == STATE_IDLE) //player dead
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = STATE_IDLE;
		}
		else if (nextState == STATE_CHASE) //Player Running
		{
			baby->itself.monsterAnimation = AnimationList[2];
			*current_state = STATE_CHASE;
		}
		else if (nextState == STATE_DIGEST) //Player eaten
		{
			baby->itself.monsterAnimation = AnimationList[4];
			*current_state = STATE_DIGEST;
		}
		break;
	}
	case STATE_LOST:
	{

		if (nextState == STATE_IDLE) //Go back to idling
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = STATE_IDLE;
		}
		else if (nextState == STATE_CHASE) //Go back to chasing if found
		{
			baby->itself.monsterAnimation = AnimationList[2];
			*current_state = STATE_CHASE;
		}
		break;
	}
	case STATE_DIGEST:
	{
		if (nextState == STATE_IDLE) //Go back to idling
		{
			baby->itself.monsterAnimation = AnimationList[0];
			*current_state = STATE_IDLE;
		}
		break;
	}
	}
}

void processing_state_baby_logic(MonsterBabyObject* baby)
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
	case STATE_IDLE:
	{
		//check facing direction, play idle animation
		//Monster facing and player is same direction
		
		if (baby->itself.facingDir > 0 && normDir.x > 0 || baby->itself.facingDir < 0 && normDir.x < 0)
		{
			if (distFromPlayer < baby->itself.detectionRange && playerRef->isHiding == 0) //Check if in range
			{
				//start alerted state
				processing_state_babyFSM(&baby->current_state, STATE_ALERT, baby);

			}
		}
		if (distFromPlayer < baby->itself.detectionRange / 1.5f && playerRef->isHiding == 0) //Check if player too close
		{
			//start alerted state

			processing_state_babyFSM(&baby->current_state, STATE_ALERT, baby);

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
				processing_state_babyFSM(&baby->current_state, STATE_PATROL, baby);
			}
			baby->itself.randTimerCheck = baby->itself.randTimerCheckOriginal;
		}
		break;
	}
	case STATE_PATROL:
	{
		//Monster facing and player is facing each other
		if (baby->itself.facingDir > 0 && normDir.x > 0 || baby->itself.facingDir < 0 && normDir.x < 0)
		{
			if (distFromPlayer < baby->itself.detectionRange && playerRef->isHiding == 0 && playerRef->toDraw == 1) //Check if in range
			{
				//start alerted state

				processing_state_babyFSM(&baby->current_state, STATE_ALERT, baby);

			}
		}

		if (distFromPlayer < baby->itself.detectionRange / 1.5f && playerRef->isHiding == 0 && playerRef->toDraw == 1) //Check if player too close
		{
			//start alerted state

			processing_state_babyFSM(&baby->current_state, STATE_ALERT, baby);

		}


		baby->itself.transform.x += baby->itself.facingDir * (baby->itself.movementSpeed * CP_System_GetDt());
		if (baby->itself.randTimerCheck <= 0.f)
		{
			if (CP_Random_RangeInt(0, 100) < 60) //50% chance to go back to idle each frame;
			{
				processing_state_babyFSM(&baby->current_state, STATE_IDLE, baby);
			}
		
			baby->itself.randTimerCheck = baby->itself.randTimerCheckOriginal;
		}
		break;
	}
	case STATE_ALERT:
	{
;
		if (distFromPlayer <= baby->itself.detectionRange && playerRef->isHiding == 0) //Check if in range
		{
			//start alerted state
			processing_state_babyFSM(&baby->current_state, STATE_CHASE, baby);

		}
		else
		{
			if (baby->itself.randTimerCheck <= 0.f)
			{
				if (CP_Random_RangeInt(0, 100) < 5) //5% chance it gets bored and goes back to idling
				{
					processing_state_babyFSM(&baby->current_state, STATE_IDLE, baby);
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

				processing_state_babyFSM(&baby->current_state, STATE_LOST, baby); //player not found
			}

		}
		break;
	}
	case STATE_CHASE:
	{
		//Check if left or right and same floor
		if (distFromPlayer < baby->itself.attackRange && playerRef->isHiding == 0)
		{
			processing_state_babyFSM(&baby->current_state, STATE_ATTACK, baby);
		}


		//If player disappears into a hiding place or gets too far
		// add LOST STATE transition here
		if (distFromPlayer > baby->itself.detectionRange * 1.5f)
		{
			processing_state_babyFSM(&baby->current_state, STATE_LOST, baby);
			baby->itself.moveTimer = baby->itself.moveTimerOriginal;
		}
		else if (playerRef->isHiding == 1 && baby->itself.moveTimer <= 0.f)
		{
			processing_state_babyFSM(&baby->current_state, STATE_LOST, baby);
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
	

		baby->itself.transform.x += baby->itself.facingDir * (baby->itself.movementSpeed * CP_System_GetDt());
		break;
	}
	case STATE_ATTACK:
	{
		//Kill player & play animation ? are we doing collision check here or guaranteed kill when reach this
		if (baby->itself.monsterAnimation.currFrameIndex == 2)
		{
			playerRef->toDraw = 0;
			playerRef->currentHealth = 0;
		}
		if (baby->itself.monsterAnimation.currFrameIndex == 3)
		{
			processing_state_babyFSM(&baby->current_state, STATE_DIGEST, baby);
		}
		break;
	}
	case STATE_DIGEST:
	{
		//Idle, play lost animation
		//End game
		break;
	}
	case STATE_LOST:
	{
		//Idle, play lost animation
		if (baby->itself.lostTimer <= 0.f)
		{
			baby->itself.lostTimer = baby->itself.lostTimerOriginal;
			processing_state_babyFSM(&baby->current_state, STATE_IDLE, baby);
		}
		else if(distFromPlayer < baby->itself.detectionRange && playerRef->isHiding == 0)
		{
			baby->itself.lostTimer = baby->itself.lostTimerOriginal;
			processing_state_babyFSM(&baby->current_state, STATE_CHASE, baby);
		}
		else
		{
			baby->itself.lostTimer -= CP_System_GetDt();
		}
		break;
	}
	}
}

void UpdateMonsterBaby()
{
	for (int i = 0; i < babyList->size; i++)
	{
		MonsterBabyObject* obj = (MonsterBabyObject*)ListGet(babyList, i);
		if (obj != NULL)
		{
			if (obj->itself.isActive == false)
			{
				continue;
			}
			processing_state_baby_logic(obj);

			Animation_Animate(&obj->itself.monsterAnimation, (obj->itself.transform.x - playerRef->currentPositionX), (obj->itself.transform.y - playerRef->currentPositionY), obj->itself.facingDir * -1, 1);

			if (obj->itself.transform.x < -(5 / 2 + 1) * 1600)
			{
				obj->itself.transform.x += 5 * 1600;
			}
			if (obj->itself.transform.x > (5 / 2 + 1) * 1600)
			{
				obj->itself.transform.x -= 5 * 1600;
			}
			//DrawSprite(obj->itself.monsterSheet, 1, 0, obj->itself.transform.x, obj->itself.transform.y, 1, 1);
			//CP_Font_DrawText(intToConstChar((int)obj->current_state), (obj->itself.transform.x - playerRef->currentPositionX), (obj->itself.transform.y - playerRef->currentPositionY));
		}
	}
}

void TeleportMonsterRoom(int amt)
{
	for (int i = 0; i < babyList->size; i++)
	{
		MonsterBabyObject* obj = (MonsterBabyObject*)ListGet(babyList, i);
		if (obj != NULL)
		{
			if (obj->itself.isActive == false)
			{
				continue;
			}
			if (obj->current_state == STATE_CHASE)
			{
				obj->itself.transform.x += amt;
				printf("Monster teleported: %f", obj->itself.transform.x);
			}
			
		}
	}
}
