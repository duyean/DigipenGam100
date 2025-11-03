#pragma once
#include "cprocessing.h"
#include "dialogueLineClass.h"

typedef struct {
    DialogueLine* lines;
    int totalLines;
    int currentLineIndex;
    CP_Image textbox;
    CP_Image currentSprite;
    CP_Image currentBackground;
    int isActive;
} DialogueSystem;
