#include "cprocessing.h"
#include "../CMP_Audio_Pak.h"
#include <stdio.h>

// mr jerome's code is here

SoundAsset CreateSound(char const* file, float volume, float pitch, CP_SOUND_GROUP group, CP_BOOL loop) {
	SoundAsset newAsset;
	newAsset.sound = group == CP_SOUND_GROUP_MUSIC ? CP_Sound_LoadMusic(file) : CP_Sound_Load(file);
	newAsset.group = group;
	newAsset.volume = volume;
	newAsset.pitch = pitch;
	newAsset.loop = loop;
	return newAsset;
}

void PlaySound(SoundAsset* asset) {
	CP_Sound_PlayAdvanced(asset->sound, asset->volume, asset->pitch, asset->pitch, asset->group);
}

void FreeSound(SoundAsset* asset) {
	CP_Sound_Free(asset->sound);
}

// jelly's fuckall code is here
// currently present in settings game and main menu, make sure to change
// after recoding this part

CP_Sound mainMenuMusic = NULL;
CP_Sound gameplayMusic = NULL;
CP_Sound soundEffects = NULL;

float masterVolume = 1.0f;
float effectiveSFX = 1.0f;
float effectiveBGM = 1.0f;