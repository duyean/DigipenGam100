#include "cprocessing.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Text_Pak.h"
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

TextTemplate settingsTextTemplate;
CP_Image settings_BG;

extern CP_Sound mainMenuMusic;
extern float volume;

float sliderX = 600.0f;
float sliderY = 250.0f;
float sliderWidth = 400.0f;
float sliderHeight = 20.0f;

bool dragging = false;

// note i havent tested the audio yet cuz no audio but i think the volume looks solid ?? ??

void draw_volume_slider() {

    // unless. we want a proper slider image but
    // i dont think we need that right hahahahha haha
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRect(sliderX + sliderWidth / 2, sliderY, sliderWidth, sliderHeight);

    float knobX = sliderX + volume * sliderWidth;
    CP_Settings_Fill(CP_Color_Create(67, 36, 17, 255));
    CP_Graphics_DrawRect(knobX, sliderY, 20, 30);
}

void handle_slider_input() {

    float mouseX = CP_Input_GetMouseX();
    float mouseY = CP_Input_GetMouseY();
    bool mousePressed = CP_Input_MouseDown(MOUSE_BUTTON_1);

    // simple bool to check if mouse down or up and within the fucking boundary
    // TAKE ME BAKC TO UNITY
    float knobX = sliderX + volume * sliderWidth;
    if (mousePressed && mouseX > knobX - 10 && mouseX < knobX + 10 && mouseY > sliderY - 15 && mouseY < sliderY + 15) {
        dragging = true;
    }
    if (!mousePressed) {
        dragging = false;
    }

    // im gonna clamp someone's neck 
    // this is the easiest way to do it right haha hahahah h..h......
    if (dragging) {
        volume = (mouseX - sliderX) / sliderWidth;
        volume = CP_Math_ClampFloat(volume, 0.0f, 1.0f); // 1.0 is max, 0.0 is mute

        CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, volume);
    }
}

void settings_menu_init(void) {

    // draw settings and the music zzz
    settings_BG = CP_Image_Load("./Assets/settings_test.png");
    mainMenuMusic = CP_Sound_Load("./Assets/Main.wav");

    settingsTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));
    CP_Font_Set(settingsTextTemplate.font);

    // this one is for bgm 
    CP_Sound_PlayAdvanced(mainMenuMusic, 1.0f, volume, TRUE, CP_SOUND_GROUP_0);

}

void settings_menu_update(void) {
    CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

    int width = CP_System_GetWindowWidth() / 2.0f;
    int height = CP_System_GetWindowHeight() / 2.0f;

    // just the BG, image placeholder
    CP_Image_Draw(settings_BG, width, height, width, width, 255);

    // volume text wow genniuuus
    CP_Settings_TextSize(100.0f);
    CP_Font_DrawText("Volume", 600.0f, 150.0f);

    // draw stupid slider
    draw_volume_slider();
    handle_slider_input();

    // mr jerome's epic code for returning to main with the insane fade
    if (CP_Input_KeyReleased(KEY_Q)) {
        StartTransition();
    }

    TransitionFadeIn(2.f, 0, 0, 0, 255);
    TransitionFadeOut(2.f, MAIN);
}

void settings_menu_exit(void) {

    // i think this works. i think idk 
    // 1 bajillion warnings
    CP_Font_Free(settingsTextTemplate.font);
}