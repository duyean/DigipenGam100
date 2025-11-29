/*---------------------------------------------------------------
  File: Slider.h
  Project: GAM100, Team ChocoMochiPie
  Author: Breanne
  Purpose: Menu sliders

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once
#include "cprocessing.h"
#include <stdbool.h>

typedef struct
{
    float x, y, width, height, knobX, knobWidth, knobHeight;
    CP_Color barColor, knobColor;

    bool isDragging;

} Slider;

void DrawSlider(Slider* s, float volume, CP_Color knobColor);
void SliderValues(Slider* s, float x, float y);
void HandleSliderInput(Slider* s, float* volume, CP_SOUND_GROUP group);

void ReturnMenu(void);
void UpdateVolumeSlider(Slider* s, float (*getVol)(), void (*setVol)(float), int group, CP_Color knobColor);

void ControlsPopUp(void);
void OpenControlsPopUp(void);
void CloseControlsPopUp(void);

extern bool isPopUpActive;