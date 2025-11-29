/*---------------------------------------------------------------
  File: qol.h
  Project: GAM100, Team ChocoMochiPie
  Author: Jerome
  Purpose: Qol

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once

CP_Vector GetMousePosition(void);
float DeltaTime();
float ElapsedTimeSeconds();
float ElapsedTimeMiliseconds();
int GetScreenHorizontalSize(void);
int GetScreenVerticalSize(void);
float changeRange(float OldValue, float OldMin, float NewMax, float NewMin, float OldMax);
