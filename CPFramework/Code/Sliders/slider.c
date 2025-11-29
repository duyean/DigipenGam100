/*---------------------------------------------------------------
  File: Slider.c
  Project: GAM100, Team ChocoMochiPie
  Author: Breanne
  Purpose: Menu sliders

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "cprocessing.h"
#include "slider.h"
#include "../CMP_Settings_Pak.h"

void DrawSlider(Slider* s, float volume, CP_Color knobColor)
{
    s->barColor = CP_Color_Create(255, 255, 255, 125);

    CP_Settings_Fill(s->barColor);
    CP_Graphics_DrawRect(s->x + s->width / 2, s->y, s->width, s->height);

    s->knobX = s->x + volume * s->width;
    CP_Settings_Fill(s->knobColor);
    CP_Graphics_DrawRect(s->knobX, s->y, s->knobWidth, s->knobHeight);
}

void SliderValues(Slider* s, float x, float y)
{
    // defines the initial color so it can change when isDragging = true
    s->knobColor = CP_Color_Create(140, 95, 55, 255);

    s->x = x;
    s->y = y;
    s->width = 400.0f;
    s->height = 20.0f;
    s->knobWidth = 20.0f;
    s->knobHeight = 30.0f;
    s->isDragging = false;
}

void HandleSliderInput(Slider* s, float* volume, CP_SOUND_GROUP group)
{
    float mouseX = CP_Input_GetMouseX();
    float mouseY = CP_Input_GetMouseY();
    bool mousePressed = CP_Input_MouseDown(MOUSE_BUTTON_1);

    // if the mouse is pressed within the knob position, then fulfills the if s->isDragging condition
    // which then just. clamps the volume within the volume bar and sets the volume of which group the slider is controlling between 0 and 1
    // depending on where the mouseX is s
    if (mousePressed && mouseX > s->knobX - s->knobWidth / 2 && mouseX < s->knobX + s->knobWidth / 2 && mouseY > s->y - s->knobHeight / 2 && mouseY < s->y + s->knobHeight / 2)
    {
        s->isDragging = true;
    }
    else if (!mousePressed)
    {
        s->isDragging = false;
    }

    if (s->isDragging)
    {
        // ts now controlled by the update
        *volume = (mouseX - s->x) / s->width;
        *volume = CP_Math_ClampFloat(*volume, 0.0f, 1.0f);
        s->knobColor = CP_Color_Create(56, 56, 56, 255);
    }
    else {
        // literally just press & hold color change
        s->knobColor = CP_Color_Create(102, 102, 102, 255);
    }
}

void UpdateVolumeSlider(Slider* s, float (*getVol)(), void (*setVol)(float), int group, CP_Color knobColor)
{
    // get refactored bozo
    float vol = getVol();
    DrawSlider(s, vol,knobColor);

    // haha cant slide with popup lol
    if (!isPopUpActive)
    {
        HandleSliderInput(s, &vol, group);
        setVol(vol);
    }
}
