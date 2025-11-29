/*---------------------------------------------------------------
  File: fileReader.c
  Project: GAM100, Team ChocoMochiPie
  Author: Daniel
  Purpose: reading of text files for dialogue

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogueLineClass.h"

#define MAX_LINES 500           //failsafe if you fuck up a big text file -day
#define MAX_LINE_LENGTH 500     //I KNOW WHAT YOU ARE -day

DialogueLine* LoadDialogueFromTextFile(const char* filename, int* outCount) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    DialogueLine* lines = malloc(sizeof(DialogueLine) * MAX_LINES);
    char buffer[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (count >= MAX_LINES) break;

        // Speaker
        char* speaker = strdup(buffer);
        speaker[strcspn(speaker, "\r\n")] = '\0';

        // Text + inline commands
        if (!fgets(buffer, sizeof(buffer), file)) break;
        char* rawText = strdup(buffer);
        rawText[strcspn(rawText, "\r\n")] = '\0';

        //pre initialise, NULL or 0 if they do not show usage! -day
        int shake = 0;
        char* soundPath = NULL; 
        char* musicPath = NULL;
        float pauseDuration = 0.0f;
        char* backgroundPath = NULL;


        char* command = strstr(rawText, "#");
		//checks for commands after the texts -day
        //it's not optimal rn but it works and I need to go for dinner so DM me to fix it another day! -day
        //if it's not fixed then fuck it we can just say oh no we were too stupid to code properly teehee -day
        //i really can't be bothered anymore you know, we keep getting sick, you, me, everyone in the team -day
        //what's it matter if the code is a little silly eh? -day
        //-day
        while (command) {
            if (strncmp(command, "#shake", 6) == 0) {
                shake = 1;
                memmove(command, command + 6, strlen(command + 6) + 1);
            }
            else if (strncmp(command, "#sound:", 7) == 0) {
                soundPath = _strdup(command + 7);
                char* end = strchr(soundPath, ' ');
                if (end) *end = '\0';
                memmove(command, command + 7 + strlen(soundPath), strlen(command + 7 + strlen(soundPath)) + 1);
            }
            else if (strncmp(command, "#music:", 7) == 0) {
                musicPath = _strdup(command + 7);
                char* end = strchr(musicPath, ' ');
                if (end) *end = '\0';
                memmove(command, command + 7 + strlen(musicPath), strlen(command + 7 + strlen(musicPath)) + 1);
            }
            else if (strncmp(command, "#pause:", 7) == 0) {
                pauseDuration = (float)atof(command + 7);
                char* end = strchr(command + 7, ' ');
                if (end) memmove(command, end + 1, strlen(end + 1) + 1);
                else break;
            }
            else if (strncmp(command, "#bg:", 4) == 0) {
                backgroundPath = _strdup(command + 4);
                char* end = strchr(backgroundPath, ' ');
                if (end) *end = '\0';
                memmove(command, command + 4 + strlen(backgroundPath), strlen(command + 4 + strlen(backgroundPath)) + 1);
            }
            else {
				printf("Unknown command in dialogue: %s\n", command); //appear in the debug console if command dosn't exist in text that is read! -day
                break;
            }

            command = strstr(rawText, "#");
        }

        // Sprite
        if (!fgets(buffer, sizeof(buffer), file)) break;
        char* sprite = strdup(buffer);
        sprite[strcspn(sprite, "\r\n")] = '\0';

        fgets(buffer, sizeof(buffer), file);  // Skip blank line

        lines[count].speaker = speaker;
        lines[count].text = rawText;
        lines[count].spritePath = sprite;
        lines[count].triggerShake = shake;
        lines[count].soundPath = soundPath;
        lines[count].musicPath = musicPath;
        lines[count].pauseDuration = pauseDuration;
        lines[count].backgroundPath = backgroundPath;

        count++;
    }

    fclose(file);
    *outCount = count;
    return lines;
}
