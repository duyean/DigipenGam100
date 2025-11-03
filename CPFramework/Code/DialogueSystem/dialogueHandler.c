#include "cprocessing.h"
#include <stdlib.h>
#include "dialogueSystemClass.h"

static float pauseTimer = 0.0f;
static int isPaused = 0;
static CP_Sound currentMusic;


void DialogueSystem_Init(DialogueSystem* ds, DialogueLine* lines, int count) {
    ds->lines = lines;
    ds->totalLines = count;
    ds->currentLineIndex = 0;
    ds->textbox = CP_Image_Load("../assets/textbox.png");
    ds->currentSprite = CP_Image_Load(lines[0].spritePath);
	ds->currentBackground = lines[0].backgroundPath ? CP_Image_Load(lines[0].backgroundPath) : NULL;
    ds->isActive = 1;
}

void DialogueSystem_Update(DialogueSystem* ds) {
    if (!ds->isActive) return;

	//handles dramatic pause durations -day
    if (isPaused) {
        pauseTimer -= CP_System_GetDt();
        if (pauseTimer <= 0) isPaused = 0;
        return;
    }

    if (CP_Input_KeyTriggered(KEY_ENTER) || (CP_Input_KeyTriggered(MOUSE_BUTTON_LEFT))) {
        ds->currentLineIndex++;
        if (ds->currentLineIndex >= ds->totalLines) {
            ds->isActive = 0;
            return;
        }

        DialogueLine* line = &ds->lines[ds->currentLineIndex];
        ds->currentSprite = CP_Image_Load(line->spritePath);

		// Play short sound bite if specified (e.g., for a screen shake or ominous sound during dialogue)
        if (line->soundPath) {
            CP_Sound sfx = CP_Sound_Load(line->soundPath);
            CP_Sound_Play(sfx);
        }

		// Play backround music if specified
        if (line->musicPath) {
            //HELP NEEDED: IDK HOW TO LOOP SOUND OR REPLAY MUSIC I NEED YOU TO DO THIS FOR ME!!! -day
            currentMusic = CP_Sound_Load(line->musicPath);
			CP_Sound_Play(currentMusic);
        }

        // Dialogue dramatic pause timer handler if specified
        if (line->pauseDuration > 0.0f) {
            pauseTimer = line->pauseDuration;
            isPaused = 1;
        }
    }
}

void DialogueSystem_Draw(DialogueSystem* ds) {
    if (!ds->isActive) return;

    DialogueLine* line = &ds->lines[ds->currentLineIndex];

    if (ds->currentBackground) {CP_Image_Draw(ds->currentBackground, 640, 360, 1280, 720, 255);}


    // Draw character sprite with optional shake
    if (line->triggerShake) {
        float shakeX = (rand() % 5) - 2;
        float shakeY = (rand() % 5) - 2;
        CP_Image_Draw(ds->currentSprite, 200 + shakeX, 200 + shakeY, 300, 400, 255);
    }
    else {
        CP_Image_Draw(ds->currentSprite, 200, 200, 300, 400, 255);
    }

    // Draw textbox
    CP_Image_Draw(ds->textbox, 640, 500, 1280, 200, 255);

    // Draw speaker and text
    CP_Settings_TextSize(24);
    //CP_Settings_TextAlignment(); //idk how to align left im running out of time pls read documentation hehe -day
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Font_DrawText(line->speaker, 100, 450);
    CP_Font_DrawText(line->text, 100, 490);
}

int DialogueSystem_IsFinished(DialogueSystem* ds) {
    return !ds->isActive;
}
