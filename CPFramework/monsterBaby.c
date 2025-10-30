#include "monsterBaby.h"
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
#include "ListFile.h"
#define ArraySize(a) (sizeof(a)/sizeof(a[0]))

List* babyList;

MonsterBabyObject* createBabyMonster(int x, int y, int patrolMax, float movementSpeed)
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
	new->itself.movementSpeed = 15.f;
	new->itself.patrolMaxLength = patrolMax;
	new->current_state = STATE_CHASE;
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
	listAdd(babyList, createBabyMonster(500, 500, 10, 15.f));
	listAdd(babyList, createBabyMonster(500, 800, 10, 15.f));

}

void processing_state_babyFSM(BABY_AI_STATE *current_state, int event)
{
	//Event == 0 no changes to event

	switch (*current_state)
	{
	case STATE_IDLE:
	{
		if (event == 1) //Nothing to do, go patrol
		{
			*current_state = STATE_PATROL;
		}
		else if (event == 2) //Alerted
		{
			*current_state = STATE_ALERT;
		}
		break;
	}
	case STATE_PATROL:
	{
		if (event == 1) //Finish Moving
		{
			*current_state = STATE_IDLE;
		}
		else if (event == 2) //Alerted
		{
			*current_state = STATE_ALERT;
		}
		break;
	}
	case STATE_ALERT:
	{
		if (event == 3) //Finish Player not found
		{
			*current_state = STATE_IDLE;
		}
		else if (event == 4) //Player Found
		{
			*current_state = STATE_CHASE;
		}
		break;
	}
	case STATE_CHASE:
	{
		if (event == 5) //Lost player
		{
			*current_state = STATE_LOST;
		}
		else if (event == 6) //Player reached
		{
			*current_state = STATE_ATTACK;
		}
		break;
	}
	case STATE_ATTACK:
	{
		if (event == 7) //player dead
		{
			*current_state = STATE_IDLE;
		}
		else if (event == 8) //Player Running
		{
			*current_state = STATE_CHASE;
		}
		break;
	}
	case STATE_LOST:
	{
		if (event == 9) //Go back to idling
		{
			*current_state = STATE_IDLE;
		}
		break;
	}
	}
}

void processing_state_baby_logic(MonsterBabyObject *baby)
{
	//Do AI Logic
	switch (baby->current_state)
	{
	case STATE_IDLE:
	{
		//do nothing, play idle animation
		break;
	}
	case STATE_PATROL:
	{
		
		break;
	}
	case STATE_ALERT:
	{
		
		break;
	}
	case STATE_CHASE:
	{
		baby->itself.transform.x -= baby->itself.movementSpeed * CP_System_GetDt();
		break;
	}
	case STATE_ATTACK:
	{
		
		break;
	}
	case STATE_LOST:
	{
	
		break;
	}
	}
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
		DrawSprite(obj->itself.monsterSheet, 1, 0, obj->itself.transform.x, obj->itself.transform.y);
	}
}
