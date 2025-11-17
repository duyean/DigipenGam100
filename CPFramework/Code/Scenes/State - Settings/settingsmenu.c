#include "cprocessing.h"
#include "settingsmenu.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Audio_Pak.h"
#include "../../CMP_Settings_Pak.h"
#include <windows.h>
#include <stdio.h>

// to do: button below the sliders "Controls" that pops up a short instruction box with just static words and images (optional)

TextTemplate settingsTextTemplate;
CP_Image settingsBG, backButtonBG, controlsButtonBG;
Button backButton, controlsButton, closePopUpButton;

Slider BGMSlider, SFXSlider, masterSlider;
bool isPopUpActive = false;

void ReturnMenu(void) {
    StartTransition();
}

void ControlsPopUp(void) {

    int width = CP_System_GetWindowWidth() / 2.0f;
    int height = CP_System_GetWindowHeight() / 2.0f;

    if (isPopUpActive) {

        // darkens the background 
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
        CP_Graphics_DrawRect(width, height, CP_System_GetWindowWidth(), CP_System_GetWindowHeight());

        // reusing settings bg
        CP_Image_Draw(settingsBG, width, height, 560.0f, 250.0f, 255);

        CP_Settings_Fill(CP_Color_Create(71, 39, 18, 255));
        CP_Settings_TextSize(60.0f);
        CP_Font_DrawText("Controls", width, height - 80.0f);

        CP_Settings_TextSize(40.0f);
        CP_Font_DrawText("Move: WASD", width, height - 20.0f);
        CP_Font_DrawText("Hide: E", width, height + 20.0f);
        CP_Font_DrawText("Pause: ESC", width, height + 60.0f);

        DrawButtonUsingImage(backButtonBG, &closePopUpButton, settingsTextTemplate);
    }
}

void settings_menu_init(void) {

    // draw settings and the music zzz
    // the filepaths need to be adjusted after merging 
    settingsBG = CP_Image_Load("./Assets/settings_test.png");
    backButtonBG = CP_Image_Load("./Assets/backButton.png");
    controlsButtonBG = CP_Image_Load("./Assets/controlsButton.png");

    // color is being controlled by the font template cuz i cant be assed
    settingsTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(71, 39, 18, 255));
    CP_Font_Set(settingsTextTemplate.font);

    backButton = CreateButton(100, 350, 80, 80, 255, &ReturnMenu);
    backButton = AddTextToButton(&backButton, "", -100, 0);

    // ts pmo
    controlsButton = CreateButton(600, 750, 250, 100, 255, &OpenControlsPopUp);
    controlsButton = AddTextToButton(&controlsButton, "Controls", 0, 0);

    closePopUpButton = CreateButton(600, 450, 50, 50, 255, &CloseControlsPopUp);
    closePopUpButton = AddTextToButton(&closePopUpButton, "", 0, 0);

    // draws the sliders and initializes their stupid positions
    SliderValues(&masterSlider, 600.0f, 250.0f);
    SliderValues(&BGMSlider, 600.0f, 400.0f);
    SliderValues(&SFXSlider, 600.0f, 550.0f);
}

void settings_menu_update(void) {

    // ts just blocks input outside the popup box 
    // not rlly necessary cuz it just blocks the other back button but whatever bruh
    if (isPopUpActive)
    {
        if (CP_Input_MouseClicked())
        {
            float x = CP_Input_GetMouseX();
            float y = CP_Input_GetMouseY();

            int width = CP_System_GetWindowWidth() / 2;
            int height = CP_System_GetWindowHeight() / 2;

            float popupWidth = 560.0f;
            float popupHeight = 250.0f;

            bool insidePopup = x > width - popupWidth / 2 && x < width + popupWidth / 2 && y > height - popupHeight / 2 && y < height + popupHeight / 2;

            if (!insidePopup)
            {
                return;
            }
        }
    }

    CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

    int width = CP_System_GetWindowWidth() / 2.0f;
    int height = CP_System_GetWindowHeight() / 2.0f;

    // placeholder BG and back button
    CP_Image_Draw(settingsBG, width, height, width, width, 255);
    DrawButtonUsingImage(backButtonBG, &backButton, settingsTextTemplate);
    DrawButtonUsingImage(controlsButtonBG, &controlsButton, settingsTextTemplate);

    // texts wow genniuuus
    CP_Settings_TextSize(100.0f);
    CP_Font_DrawText("Master Volume", 700.0f, 150.0f);
    CP_Font_DrawText("Volume", 600.0f, 325.0f);
    CP_Font_DrawText("Sound Effects", 700.0f, 485.0f);

    CP_Color knobColor = CP_Color_Create(102, 102, 102, 255);

    UpdateVolumeSlider(&BGMSlider, AudioGetBGMVolume, AudioSetBGMVolume, 0, knobColor);
    UpdateVolumeSlider(&SFXSlider, AudioGetSFXVolume, AudioSetSFXVolume, 1, knobColor);
    UpdateVolumeSlider(&masterSlider, AudioGetMasterVolume, AudioSetMasterVolume, -1, knobColor);

    ControlsPopUp();

    TransitionFadeIn(2.f, 0, 0, 0, 255);
    TransitionFadeOut(2.f, MAIN);
}

void settings_menu_exit(void) {

    // don't free the music, we need it to run globally
    CP_Font_Free(settingsTextTemplate.font);
}