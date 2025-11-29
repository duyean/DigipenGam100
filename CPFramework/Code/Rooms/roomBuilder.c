/*---------------------------------------------------------------
  File: roomBuilder
  Project: GAM100, Team ChocoMochiPie
  Author: Daniel
  Purpose: room builder

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include <stdio.h>
#include "cprocessing.h"
#include "../CMP_Room_Pak.h"

//for random
#include <stdlib.h>
#include <time.h>

//Defining my insanity. -day
Room GenerateRoom(Room rooms[], int number_default, int instruct)
{
	if (instruct) return rooms[0];
    return rooms[1 + rand() % number_default];
}