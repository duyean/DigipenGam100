#include "cprocessing.h"
#include "sound.h"
#include <stdio.h>

SoundAsset CreateSound(char const *file, float volume, float pitch, CP_SOUND_GROUP group, CP_BOOL loop) {
	SoundAsset newAsset;
	newAsset.sound = group == CP_SOUND_GROUP_MUSIC ? CP_Sound_LoadMusic(file) : CP_Sound_Load(file);
	newAsset.group = group;
	newAsset.volume = volume;
	newAsset.pitch = pitch;
	newAsset.loop = loop;
	return newAsset;
}

void PlaySound(SoundAsset *asset) {
	CP_Sound_PlayAdvanced(asset->sound, asset->volume, asset->pitch, asset->pitch, asset->group);
}

void FreeSound(SoundAsset *asset) {
	CP_Sound_Free(asset->sound);
}