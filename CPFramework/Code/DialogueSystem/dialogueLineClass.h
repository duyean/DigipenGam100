#pragma once

typedef struct {
    const char* speaker;
    const char* text;
    const char* spritePath;
    int triggerShake;
    const char* soundPath;
    const char* musicPath;
    float pauseDuration;
    const char* backgroundPath;
} DialogueLine;