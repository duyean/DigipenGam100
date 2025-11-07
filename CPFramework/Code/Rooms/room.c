#include <stdio.h>
#include "cprocessing.h"
#include "roomClass.h"
#include "../CMP_Interactable_Pak.h"
#include "../CMP_Sprite_Pak.h"
#include "../CMP_Player_Pak.h"

Room Room_Create(Spritesheet room[], SpriteData frame[], int size, int xPos, int yPos, Interactable interactables[4], int arrNum)
{
	static Room newRoom;
	for (int i = 0; i < size; i++)
	{
		newRoom.roomItem[i] = room[i];
		newRoom.frame[i] = frame[i];
	}

	newRoom.xPos = xPos;
	newRoom.yPos = yPos;
	for (int i = 0; i < arrNum; i++) { newRoom.interractibles[i] = interactables[i]; }
	newRoom.interactibleCount = arrNum;
	return newRoom;
}

void Room_Load(Room *room, int size, Player player)
{
	// Set up background
	for (int i = 0; i < size; i++)
	{
		if (i == 1)
		{
			Sprite_Draw(room->roomItem[i], room->frame[i], room->xPos - player.currentPositionX, room->yPos - 210, 1, 1);
		}
		else if (i == 2)
		{
			Sprite_Draw(room->roomItem[i], room->frame[i], room->xPos - player.currentPositionX, room->yPos, 1, 1);
		}
		else
		{
			Sprite_Draw(room->roomItem[i], room->frame[i], room->xPos - player.currentPositionX, room->yPos, 1, 1);
		}
	}
	// Set up interactable objects HERE!!! (undone)
	//for (int i = 0; i < room->interactibleCount; i++) 
	//{ 
	//	// Draw each interactable here please.
	//}
	//DO NOT DRAW PARALLEX HERE BECAUSE THEN IT WILL ALWAYS BE BEHIND PLAYER!!! (ENSURE DO NOT DRAW PARALLEX HERE!) -day
}

// Overloaded function to allow for x position offset
void Room_LoadO(Room* room, int size, Player player, int xPosit)
{
	// Set up background
	for (int i = 0; i < size; i++)
	{
	
		if (i == 1)
		{
			Sprite_Draw(room->roomItem[i], room->frame[i], xPosit - player.currentPositionX, room->yPos - 210, 1, 1);
		}
		else if (i == 2)
		{
			Sprite_Draw(room->roomItem[i], room->frame[i], xPosit - player.currentPositionX, room->yPos, 1, 1);
		}
		else
		{
			Sprite_Draw(room->roomItem[i], room->frame[i], xPosit - player.currentPositionX, room->yPos, 1, 1);
		}
	}
	// Set up interactable objects HERE!!! (undone)
	//for (int i = 0; i < room->interactibleCount; i++)
	//{
	//	// Draw each interactable here please.
	//}
	//DO NOT DRAW PARALLEX HERE BECAUSE THEN IT WILL ALWAYS BE BEHIND PLAYER!!! (ENSURE DO NOT DRAW PARALLEX HERE!) -day
}