/*---------------------------------------------------------------
  File: audio.h
  Project: GAM100, Team ChocoMochiPie
  Author: Breanne, Jerome
  Purpose: Audio controller

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#pragma once
#include "cprocessing.h"
#include "audioClass.h"

SoundAsset CreateSound(char* file, float volume, float pitch, CP_SOUND_GROUP group, CP_BOOL loop);
void PlaySound(SoundAsset* asset);
void FreeSound(SoundAsset* asset);

void AudioInitialize();
void AudioSetMasterVolume(float volume);
void AudioSetBGMVolume(float volume);
void AudioSetSFXVolume(float volume);

float AudioGetMasterVolume(void);
float AudioGetBGMVolume(void);
float AudioGetSFXVolume(void);

void AudioPlayMainMenuMusic(void);
void AudioPlayGameplayMusic(void);
void AudioPlaySFX(CP_Sound sound);

void Audio_Unload(void);