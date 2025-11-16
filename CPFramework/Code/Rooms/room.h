#pragma once

#include "roomClass.h"

#include "../CMP_Interactable_Pak.h"
#include "../CMP_Player_Pak.h"
#include "../CMP_Sprite_Pak.h"

Room Room_Create(Spritesheet roomComponents[], SpriteData frame[], int componentsCount, Interactable *interactables[], int interactableCount);
void Room_Load(Room* room, Player player, int position);