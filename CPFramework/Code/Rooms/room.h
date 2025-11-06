#pragma once

#include "roomClass.h"

#include "../CMP_Interactable_Pak.h"
#include "../CMP_Sprite_Pak.h"

Room createRoom(Spritesheet room, SpriteData frame, int xPos, int yPos, Interactable interactables[4], int arrNum);
void loadRoom(Spritesheet room, SpriteData frame, int xPos, int yPos, Interactable interactables[4], int arrNum);