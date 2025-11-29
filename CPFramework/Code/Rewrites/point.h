/*---------------------------------------------------------------
  File: point.h
  Project: GAM100, Team ChocoMochiPie
  Author: Edmund
  Purpose: score system and saver

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once
#ifndef _points_h_
#define _points_h_

#include <stdio.h>
#include <stdlib.h>


#define FILENAME "../../Save/scoreSystem.txt"
#define KEY 8008135676767

void saveScore(int score);
int setScore(int score, int level, float timeTaken);
int viewScore(void);

#endif
