/*---------------------------------------------------------------
  File: utils.c
  Project: GAM100, Team ChocoMochiPie
  Author: Daniel
  Purpose: Utils file

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "Code/CMP_Scene_Pak.h"

void (*transitionToSceneFunc) (SceneEnum);
void InitialiseUtilities(void) {transitionToSceneFunc = SetScene;}

//I've cleaned up all the functions and organised them -day hehehe