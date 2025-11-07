#pragma once

#include "roomClass.h"

#include "../CMP_Interactable_Pak.h"
#include "../CMP_Player_Pak.h"
#include "../CMP_Sprite_Pak.h"

Room Room_Create(Spritesheet room[], SpriteData frame[], int size, int xPos, int yPos, Interactable interactables[4], int arrNum);
void Room_Load(Room* room, int size, Player player);
void Room_LoadO(Room* room,int size, Player player, int xPosit);