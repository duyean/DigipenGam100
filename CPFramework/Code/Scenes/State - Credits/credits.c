#include "cprocessing.h"
#include "credits.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Audio_Pak.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

CP_Image digipenLogo, backButtonBG;
TextTemplate creditsTextTemplate;
Button backButton;

// cough its a repeat cough
void returnMenu(void) {
    StartTransition();
}

// ts just a simple static screen for credits lallala idk if ya'll want it dynamic
// but after the bs with soroor and digipen maybe this is enough bruh

void credits_init(void) {

    digipenLogo = CP_Image_Load("./Assets/DigiPen_Singapore_WEB_RED.png");
    backButtonBG = CP_Image_Load("./Assets/backButton.png");

    creditsTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(0, 0, 0, 255));

    CP_Font_Set(creditsTextTemplate.font);

    backButton = CreateButton(100, 350, 80, 80, 255, &returnMenu);
    backButton = AddTextToButton(&backButton, "", -100, 0);
}

void credits_update(void) {

    CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

    int width = CP_System_GetWindowWidth() / 2.0f;
    int height = CP_System_GetWindowHeight() / 2.0f;

    CP_Image_Draw(digipenLogo, width, height - 200.0f, width, 225.0f, 255);
    DrawButtonUsingImage(backButtonBG, &backButton, creditsTextTemplate);

    CP_Font_DrawText("Team Members:", width, 450.0f);
    CP_Font_DrawText("Daniel, Jerome, Edmund, Breanne", width, 500.0f);

    CP_Font_DrawText("Instructors:", width, 600.0f);
    CP_Font_DrawText("Gerald, Dr. Soroor, Tommy", width, 650.0f);

    TransitionFadeIn(2.f, 0, 0, 0, 255);
    TransitionFadeOut(2.f, MAIN);
}

void credits_exit(void) {

}