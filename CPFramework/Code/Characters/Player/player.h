/*---------------------------------------------------------------
  File: player.h
  Project: GAM100, Team ChocoMochiPie
  Author: Jerome, Daniel, Edmund
  Purpose: Player controller

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once

#include "../../CMP_Sprite_Pak.h"
#include "../../CMP_Interactable_Pak.h"
#include "../Player/playerClass.h"


void Player_Initialise(Player *player);
void Player_Update(Player *player);
Spritesheet GetPlayerSheet(void);
Player* GetPlayer(void);
void Player_CheckInteractables(Interactable* interactables[], int count, float relativePosition);

void Player_StaminaUpdate(Player* player);
void Player_OilUpdate(Player* player);

void Player_Unload(void);
