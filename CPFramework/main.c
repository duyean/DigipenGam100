/*---------------------------------------------------------------
  File: main.c
  Project: GAM100, Team ChocoMochiPie
  Author: all
  Purpose: Main driver

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "cprocessing.h"
#include "utils.h"
#include "Code/CMP_Scene_Pak.h"

//THIS IS THE STARTING FILE. GENESIS, THE BEGINNING AND THE END
int main(void)
{
	InitialiseUtilities();
	SetScene(INTRO);
	
	CP_Engine_Run(1);
	return 0;
}