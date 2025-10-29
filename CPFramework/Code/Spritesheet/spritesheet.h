#pragma once

#include "spriteClass.h" //required for Spritesheet type

Spritesheet CreateSpritesheet(CP_Image source, int w, int h);
void DrawSprite(Spritesheet sheet, int column, int row, int x, int y, int flipX, int flipY);