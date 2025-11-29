/*---------------------------------------------------------------
  File: room.h
  Project: GAM100, Team ChocoMochiPie
  Author: Daniel
  Purpose: room generation code

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once

#include "roomClass.h"

#include "../CMP_Interactable_Pak.h"
#include "../CMP_Player_Pak.h"
#include "../CMP_Sprite_Pak.h"

Room Room_Create(Spritesheet roomComponents[], SpriteData frame[], int roomBG, int componentsCount, Interactable *interactables[], int interactableCount);
void Room_Load(Room* room, Player player, int position);