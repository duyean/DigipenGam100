/*---------------------------------------------------------------
  File: fileReader.h
  Project: GAM100, Team ChocoMochiPie
  Author: Daniel
  Purpose: reading of text files for dialogue

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once
#include "dialogueLineClass.h"

DialogueLine* LoadDialogueFromTextFile(const char* filename, int* outCount);