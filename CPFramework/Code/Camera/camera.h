#pragma once

#include "cameraClass.h"

void CreateCamera(Camera* cam, float x, float y);
void UpdateCamera(Camera* cam, float playerX, float playerY, float playerDX, float playerDY, float smoothing);