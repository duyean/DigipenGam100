#pragma once

#include "../../CMP_Sprite_Pak.h"
#include "../../CMP_Interactable_Pak.h"
#include "../Player/playerClass.h"

//suggest to add
int KillPlayer(Player* player);


void Player_Initialise(Player *player);
void Player_Update(Player *player);
Spritesheet GetPlayerSheet(void);
Player* GetPlayer(void);
void Player_CheckInteractables(Interactable* interactables[], int count);

void Player_StaminaUpdate(Player* player);
void Player_OilUpdate(Player* player);
