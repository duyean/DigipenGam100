/*---------------------------------------------------------------
  File: room.c
  Project: GAM100, Team ChocoMochiPie
  Author: Daniel
  Purpose: room generation code

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include <stdio.h>
#include "cprocessing.h"
#include "roomClass.h"
#include <time.h> 
#include "../CMP_Interactable_Pak.h"
#include "../CMP_Sprite_Pak.h"
#include "../CMP_Player_Pak.h"

Room Room_Create(Spritesheet roomComponents[], SpriteData frame[], int roomBG, int componentsCount, Interactable *interactables[], int interactableCount)
{
	static Room newRoom;

	int randBg = CP_Random_RangeInt(0, roomBG);
	newRoom.roomComponents[0] = roomComponents[randBg];
	newRoom.frame[0] = frame[randBg];

	for (int i = 1; i < componentsCount; i++)
    {
	   newRoom.roomComponents[i] = roomComponents[roomBG + i];
	   newRoom.frame[i] = frame[roomBG + i];
    }

	for (int i = 0; i < interactableCount; i++) { newRoom.interractibles[i] = interactables[i]; }

	newRoom.interactibleCount = interactableCount;
	newRoom.componentCount = componentsCount;
	return newRoom;
}

void Room_Load(Room* room, Player player, int position)
{
	int roomPos = position * 1600;
	float relativePos = (float)roomPos - player.currentPositionX;

	// Set up background
	for (int i = 0; i < room->componentCount; i++)
	{
		switch (i)
		{
			case 1: //??? Idk have to ask edmund what the fuck this is 卧槽这个是什么？？？
				Sprite_Draw(room->roomComponents[i], room->frame[i], relativePos, - 210, 1, 1);
				break;
			default:
				Sprite_Draw(room->roomComponents[i], room->frame[i], relativePos, 0, 1, 1);
				break;
	}	}
	for (int i = 0; i < room->interactibleCount; i++)
	{
		Interactable_Update(room->interractibles[i], relativePos + room->interractibles[i]->worldXPosition, room->interractibles[i]->worldYPosition);
	}

	Player_CheckInteractables(room->interractibles, room->interactibleCount, (float)roomPos);
}