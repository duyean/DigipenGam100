#include "cprocessing.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Text_Pak.h"
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

/*/ NOTENOTE NOTEEEE PSPSPSPS

    SFX isn't tested yet, waiting for ya'll to cook up the monster
    and player event system
    but if the effectiveBGM works then the effectiveSFX should (BY RIGHT!) work

    OH AND the extern variables should be all controlled in audio.c IN THE FUTURE so
    i'll fix up the optimisation another time or if whoever wants to do
    it go ahead brah

    and to clarify a bit effectiveSFX and effectiveBGM is just their effective volume for their
    respective category, cuz i didn't know how else to name them
    master volume as of rn is still in WIP cuz the logic is fucky in my head

/*/

TextTemplate settingsTextTemplate;
CP_Image settingsBG;

extern CP_Sound mainMenuMusic;
extern CP_Sound gameplayMusic;
extern CP_Sound soundEffects;

extern float masterVolume;
extern float effectiveSFX;
extern float effectiveBGM;

typedef struct
{
    float x, y, width, height, knobX, knobWidth, knobHeight;
    CP_Color barColor, knobColor;

    bool isDragging;

} Slider;

Slider BGMSlider;
Slider SFXSlider;
Slider masterSlider;

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

// this was so unnecessary but im keeping it here for a while to remind myself of my STUPIDITY
//void static DrawBGMSlider(Slider* s) {
//
//    s->x = 600.0f, s->y = 250.0f, s->width = 400.0f, s->height = 20.0f;
//    s->barColor = CP_Color_Create(255,255,255,125);
//    s->knobColor = CP_Color_Create(140, 95, 55, 255);
//
//    CP_Settings_Fill(s->barColor);
//    CP_Graphics_DrawRect(s->x + s->width / 2, s->y, s->width, s->height);
//
//    s->knobX = s->x + effectiveBGM * s->width;
//    CP_Settings_Fill(s->knobColor);
//    CP_Graphics_DrawRect(s->knobX, s->y, s->knobWidth, s->knobHeight);
//
//}
//
//void DrawSFXSlider(Slider * s) {
//
//    s->x = 600.0f, s->y = 400.0f, s->width = 400.0f, s->height = 20.0f;
//    s->barColor = CP_Color_Create(255, 255, 255, 125);
//    s->knobColor = CP_Color_Create(140, 95, 55, 255);
//
//    CP_Settings_Fill(s->barColor);
//    CP_Graphics_DrawRect(s->x + s->width / 2, s->y, s->width, s->height);
//
//    s->knobX = s->x + effectiveSFX * s->width;
//    CP_Settings_Fill(s->knobColor);
//    CP_Graphics_DrawRect(s->knobX, s->y, s->knobWidth, s->knobHeight);
//}

//void static HandleSliderInput(Slider* s) {
//
//    float mouseX = CP_Input_GetMouseX();
//    float mouseY = CP_Input_GetMouseY();
//
//    bool mousePressed = CP_Input_MouseDown(MOUSE_BUTTON_1);
//
//    if (mousePressed)
//    {
//        if (mouseX > BGMSlider.knobX - 10 && mouseX < BGMSlider.knobX + 10 && mouseY > BGMSlider.y - 15 && mouseY < BGMSlider.y + 15)
//        {
//            BGMSlider.isDragging = true;
//        }
//        else if (mouseX > SFXSlider.knobX - 10 && mouseX < SFXSlider.knobX + 10 && mouseY > SFXSlider.y - 15 && mouseY < SFXSlider.y + 15)
//        {
//            SFXSlider.isDragging = true;
//        }
//    }
//
//    if (!mousePressed)
//    {
//        BGMSlider.isDragging = false;
//        SFXSlider.isDragging = false;
//    }
//
//    if (BGMSlider.isDragging) {
//        effectiveBGM = (mouseX - s->x) / s->width;
//        effectiveBGM = CP_Math_ClampFloat(effectiveBGM, 0.0f, 1.0f); // 1.0 is max, 0.0 is mute
//
//        CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, effectiveBGM);
//    }
//    else if (SFXSlider.isDragging) {
//        effectiveSFX = (mouseX - s->x) / s->width;
//        effectiveSFX = CP_Math_ClampFloat(effectiveSFX, 0.0f, 1.0f); // 1.0 is max, 0.0 is mute
//
//        CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, effectiveSFX);
//    }
//}

// go ahead and refactor more if anyone wants to but i think this is as short as it can get
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
        *volume = (mouseX - s->x) / s->width;
        *volume = CP_Math_ClampFloat(*volume, 0.0f, 1.0f);
        CP_Sound_SetGroupVolume(group, *volume);

        s->knobColor = CP_Color_Create(60, 40, 20, 255);
    }
    else {
        // literally just press & hold color change
        s->knobColor = CP_Color_Create(140, 95, 55, 255);
    }
}

void settings_menu_init(void) {

    // draw settings and the music zzz
    // the filepaths need to be adjusted after merging 
    settingsBG = CP_Image_Load("./Assets/settings_test.png");
    mainMenuMusic = CP_Sound_Load("./Assets/Main.wav");

    settingsTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));
    CP_Font_Set(settingsTextTemplate.font);

    // draws the slider and initializes their stupid positions
    SliderValues(&BGMSlider, 600.0f, 250.0f);
    SliderValues(&SFXSlider, 600.0f, 400.0f);
}

void settings_menu_update(void) {

    CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

    int width = CP_System_GetWindowWidth() / 2.0f;
    int height = CP_System_GetWindowHeight() / 2.0f;

    // just the BG, image placeholder
    CP_Image_Draw(settingsBG, width, height, width, width, 255);

    // volume text wow genniuuus
    CP_Settings_TextSize(100.0f);
    CP_Settings_Fill(CP_Color_Create(71, 39, 18, 255));
    CP_Font_DrawText("Volume", 600.0f, 150.0f);

    // sound effects text
    CP_Settings_TextSize(100.0f);
    CP_Settings_Fill(CP_Color_Create(71, 39, 18, 255));
    CP_Font_DrawText("Sound Effects", 700.0f, 325.0f);

    // draw stupid slider and assigns them their sound groups + volume
    DrawSlider(&BGMSlider, effectiveBGM);
    HandleSliderInput(&BGMSlider, &effectiveBGM, CP_SOUND_GROUP_MUSIC);

    DrawSlider(&SFXSlider, effectiveSFX);
    HandleSliderInput(&SFXSlider, &effectiveSFX, CP_SOUND_GROUP_SFX);

    // mr jerome's epic code for returning to main with the insane fade
    if (CP_Input_KeyReleased(KEY_Q)) {

        StartTransition();

    }

    TransitionFadeIn(2.f, 0, 0, 0, 255);
    TransitionFadeOut(2.f, MAIN);
}

void settings_menu_exit(void) {

    // don't free the music, we need it to run globally
    CP_Font_Free(settingsTextTemplate.font);
}