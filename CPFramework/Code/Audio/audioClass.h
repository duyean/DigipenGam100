#pragma once

#include "cprocessing.h"

typedef struct {
	CP_Sound sound;
	float volume;
	float pitch;
	CP_SOUND_GROUP group;
	CP_BOOL loop;
}SoundAsset;