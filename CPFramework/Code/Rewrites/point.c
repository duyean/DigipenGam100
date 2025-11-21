#include "point.h"

void saveScore(int score)
{

	FILE* fp = fopen(FILENAME, "a");

	if (fp == NULL)
	{
		perror("Error opening save file");
		return;
	}
	int encryptedScore = score ^ KEY;

	fprintf(fp, "%d\n", encryptedScore);
	fclose(fp);

}

int setScore(int score, int level, float timeTaken)
{
	return score + ((int)((10 * (level * level)) + (((120.f - timeTaken) / 120) * 100) * level));

}


int viewScore(void)
{
	FILE* fp = fopen(FILENAME, "r");
	char buffer[1000];

	if (fp == NULL) {
		perror("File not found");
		return;
	}

	int highScore = 0;
	while (fgets(buffer, 1000, fp) != NULL)
	{
		int readValue = atoi(buffer);

		int decryptedScore = readValue ^ KEY;

		if (decryptedScore > highScore)
		{
			highScore = decryptedScore;
		}

	}

	fclose(fp);
	return highScore;

}
