/*---------------------------------------------------------------
  File: camera.h
  Project: GAM100, Team ChocoMochiPie
  Author: Jerome, Daniel
  Purpose: camera class for moving of camera n functions

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once

#include "cameraClass.h"

void CreateCamera(Camera* cam, float x, float y);
void UpdateCamera(Camera* cam, float playerX, float playerY, float playerDX, float playerDY, float smoothing);