#pragma once
#include "cprocessing.h"
#include "audioClass.h"

SoundAsset CreateSound(char* file, float volume, float pitch, CP_SOUND_GROUP group, CP_BOOL loop);
void PlaySound(SoundAsset* asset);
void FreeSound(SoundAsset* asset);