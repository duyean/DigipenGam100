/*---------------------------------------------------------------
  File: button.h
  Project: GAM100, Team ChocoMochiPie
  Author: Breanne, Jerome
  Purpose: buttons to press for mainmenu

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once
#include "cprocessing.h"
#include "buttonClass.h" //required for Button type
#include "../CMP_Text_Pak.h" //required for TextTemplate type

CP_Image DrawButtonUsingImage(CP_Image loadedImage, Button* button, TextTemplate texT);
Button CreateButton(float x, float y, float w, float h, int a, void* buttonFunc);
Button AddTextToButton(Button* button, char* text, int xOffset, int yOffset);
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);