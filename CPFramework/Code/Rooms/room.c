#include <stdio.h>
#include "cprocessing.h"
#include "roomClass.h"
#include "../CMP_Interactable_Pak.h"
#include "../CMP_Sprite_Pak.h"

Room Room_Create(Spritesheet room, SpriteData frame, int xPos, int yPos, Interactable interactables[4], int arrNum)
{
	static Room newRoom;
	newRoom.room = room;
	newRoom.frame = frame;
	newRoom.xPos = xPos;
	newRoom.yPos = yPos;
	for (int i = 0; i < arrNum; i++) { newRoom.interractibles[i] = interactables[i]; }
	newRoom.interactibleCount = arrNum;
	return newRoom;
}

void Room_Load(Room *room)
{
	//Spritesheet room, SpriteData frame, int xPos, int yPos, Interactable interactables[4], int arrNum
	// Set up background
	Sprite_Draw(room->room, room->frame, room->xPos, room->yPos, 1, 1);
	// Set up interactable objects HERE!!! (undone)
	//for (int i = 0; i < room->interactibleCount; i++) 
	//{ 
	//	// Draw each interactable here please.
	//}
	//DO NOT DRAW PARALLEX HERE BECAUSE THEN IT WILL ALWAYS BE BEHIND PLAYER!!! (ENSURE DO NOT DRAW PARALLEX HERE!) -day
}