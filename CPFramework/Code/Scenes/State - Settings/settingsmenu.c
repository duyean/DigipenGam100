#include "cprocessing.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Text_Pak.h"
#include "../../CMP_Audio_Pak.h"
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// to do: button below the sliders "Controls" that pops up a short instruction box with just static words and images (optional)

TextTemplate settingsTextTemplate;
CP_Image settingsBG, backButtonBG;
Button backButton;

typedef struct
{
    float x, y, width, height, knobX, knobWidth, knobHeight;
    CP_Color barColor, knobColor;

    bool isDragging;

} Slider;

Slider BGMSlider, SFXSlider, masterSlider;

void DrawSlider(Slider* s, float volume)
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
        s->knobColor = CP_Color_Create(60, 40, 20, 255);
    }
    else {
        // literally just press & hold color change
        s->knobColor = CP_Color_Create(140, 95, 55, 255);
    }
}

void ReturnMenu(void) {
    StartTransition();
}

void UpdateVolumeSlider(Slider* slider, float (*getVol)(), void (*setVol)(float), int group)
{
    // get refactored bozo
    float vol = getVol();
    DrawSlider(slider, vol);
    HandleSliderInput(slider, &vol, group);
    setVol(vol);
}

void settings_menu_init(void) {

    // draw settings and the music zzz
    // the filepaths need to be adjusted after merging 
    settingsBG = CP_Image_Load("./Assets/settings_test.png");
    backButtonBG = CP_Image_Load("./Assets/backButton.png");

    backButton = CreateButton(100, 350, 80, 80, 255, &ReturnMenu);
    backButton = AddTextToButton(&backButton, "", -100, 0);

    settingsTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));
    CP_Font_Set(settingsTextTemplate.font);

    // draws the sliders and initializes their stupid positions
    SliderValues(&masterSlider, 600.0f, 250.0f);
    SliderValues(&BGMSlider, 600.0f, 400.0f);
    SliderValues(&SFXSlider, 600.0f, 550.0f);
}

void settings_menu_update(void) {

    CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

    int width = CP_System_GetWindowWidth() / 2.0f;
    int height = CP_System_GetWindowHeight() / 2.0f;

    // placeholder BG and back button
    CP_Image_Draw(settingsBG, width, height, width, width, 255);
    DrawButtonUsingImage(backButtonBG, &backButton, settingsTextTemplate);

    // texts wow genniuuus
    CP_Settings_TextSize(100.0f);
    CP_Settings_Fill(CP_Color_Create(71, 39, 18, 255));
    CP_Font_DrawText("Master Volume", 700.0f, 150.0f);
    CP_Font_DrawText("Volume", 600.0f, 325.0f);
    CP_Font_DrawText("Sound Effects", 700.0f, 485.0f);

    UpdateVolumeSlider(&BGMSlider, AudioGetBGMVolume, AudioSetBGMVolume, 0);
    UpdateVolumeSlider(&SFXSlider, AudioGetSFXVolume, AudioSetSFXVolume, 1);
    UpdateVolumeSlider(&masterSlider, AudioGetMasterVolume, AudioSetMasterVolume, -1);

    TransitionFadeIn(2.f, 0, 0, 0, 255);
    TransitionFadeOut(2.f, MAIN);
}

void settings_menu_exit(void) {

    // don't free the music, we need it to run globally
    CP_Font_Free(settingsTextTemplate.font);
}