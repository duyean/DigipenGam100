/*---------------------------------------------------------------
  File: audio.c
  Project: GAM100, Team ChocoMochiPie
  Author: Breanne, Jerome
  Purpose: Audio controller

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "cprocessing.h"
#include "../CMP_Audio_Pak.h"
#include <stdio.h>

int mainMenuPlaying = 0;

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
	CP_Sound_PlayAdvanced(asset->sound, asset->volume, asset->pitch, 0, asset->group);
}

void FreeSound(SoundAsset* asset) {
	CP_Sound_Free(asset->sound);
}

CP_Sound soundEffects = NULL; // 0
CP_Sound mainMenuMusic = NULL; // 1
CP_Sound gameplayMusic = NULL; // 2

float masterVolume = 1.0f;
float effectiveSFX = 1.0f;
float effectiveBGM = 1.0f;

void AudioInitialize(void)
{
	mainMenuMusic = CP_Sound_Load("./Assets/Audio/Main.wav");
	gameplayMusic = CP_Sound_Load("./Assets/Audio/Eerie.wav");

	//CP_Sound_PlayAdvanced(mainMenuMusic, effectiveBGM, 1.0f, TRUE, CP_SOUND_GROUP_1);

	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_1, effectiveBGM);
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_2, effectiveBGM);

	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, effectiveSFX);
}

void AudioSetMasterVolume(float volume)
{
	masterVolume = volume;

	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_1, effectiveBGM * masterVolume);
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_2, effectiveBGM * masterVolume);
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, effectiveSFX * masterVolume);
}

void AudioSetBGMVolume(float volume)
{
	effectiveBGM = volume;

	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_1, effectiveBGM * masterVolume);
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_2, effectiveBGM * masterVolume);
}

void AudioSetSFXVolume(float volume)
{
	effectiveSFX = volume;

	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, effectiveSFX * masterVolume);
}

float AudioGetMasterVolume(void) { return masterVolume; }
float AudioGetBGMVolume(void) { return effectiveBGM; }
float AudioGetSFXVolume(void) { return effectiveSFX; }

void AudioPlayMainMenuMusic(void)
{
	
	CP_Sound_StopGroup(CP_SOUND_GROUP_2);
	if (mainMenuPlaying == 0)
	{
		CP_Sound_PlayAdvanced(mainMenuMusic, effectiveBGM * masterVolume, 1.0f, TRUE, CP_SOUND_GROUP_1);
		mainMenuPlaying = 1;
	}
	
}

void AudioPlayGameplayMusic(void)
{
	CP_Sound_StopGroup(CP_SOUND_GROUP_1);
	mainMenuPlaying = 0;
	CP_Sound_PlayAdvanced(gameplayMusic, effectiveBGM * masterVolume, 1.0f, TRUE, CP_SOUND_GROUP_2);
}

void AudioPlaySFX(CP_Sound sound)
{
	CP_Sound_PlayAdvanced(sound, effectiveSFX * masterVolume, 1.0f, FALSE, CP_SOUND_GROUP_0);
}

void Audio_Unload(void) {
	CP_Sound_Free(mainMenuMusic);
	CP_Sound_Free(soundEffects);
	CP_Sound_Free(gameplayMusic);
}