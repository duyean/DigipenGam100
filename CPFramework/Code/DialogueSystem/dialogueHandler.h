/*---------------------------------------------------------------
  File: dialogueHandler.h
  Project: GAM100, Team ChocoMochiPie
  Author: Daniel
  Purpose: dialogue system controller

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once
#include "dialogueSystemClass.h"
#include "dialogueLineClass.h"
#include <stdbool.h>

void DialogueSystem_Init(DialogueSystem* ds, DialogueLine* lines, int count);
void DialogueSystem_Update(DialogueSystem* ds);
void DialogueSystem_Draw(DialogueSystem* ds);
bool DialogueSystem_IsFinished(DialogueSystem* ds);
