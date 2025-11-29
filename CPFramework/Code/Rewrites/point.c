/*---------------------------------------------------------------
  File: point.c
  Project: GAM100, Team ChocoMochiPie
  Author: Edmund
  Purpose: score system and saver

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "point.h"

void saveScore(int score)
{

	FILE* fp = fopen(FILENAME, "a");

	if (fp == NULL)
	{
		perror("Error opening save file");
		return;
	}
	int encryptedScore = score ^ (int)KEY;

	fprintf(fp, "%d\n", encryptedScore);
	fclose(fp);

}

int setScore(int score, int level, float timeTaken)
{
	return score + ((int)((10 * (level * level)) + (((180.f - timeTaken) / 180) * 100) * level));

}


int viewScore(void)
{
	FILE* fp = fopen(FILENAME, "r");
	char buffer[1000];

	if (fp == NULL) {
		perror("File not found");
		return 0;
	}

	int highScore = 0;
	while (fgets(buffer, 1000, fp) != NULL)
	{
		int readValue = atoi(buffer);

		int decryptedScore = readValue ^ (int)KEY;

		if (decryptedScore > highScore)
		{
			highScore = decryptedScore;
		}

	}

	fclose(fp);
	return highScore;

}
