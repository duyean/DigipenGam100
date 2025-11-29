/*---------------------------------------------------------------
  File: spritesheet.c
  Project: GAM100, Team ChocoMochiPie
  Author: Jerome
  Purpose: spritesheet loader

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "spriteClass.h"
#include <stdio.h>
#include <stdlib.h>

/*
* Uses the CP_Image as a source, the width and height of Each Sprite
* Return: Initialized Spritesheet
* Uses: Sprite_Draw(), Animation_Create()
* Sub-uses: Animation_Animate->Animation
*/
Spritesheet Spritesheet_Create(CP_Image source, int spriteW, int spriteH) {
	static Spritesheet sheet;
	sheet.source = source;
	sheet.width = CP_Image_GetWidth(source);
	sheet.height = CP_Image_GetHeight(source);
	sheet.spriteWidth = spriteW;
	sheet.spriteHeight = spriteH;

	return sheet;
}

/*Creates data the will contain the Drawn Size of the Sprite, and the Row and Column within a Spritesheet*/
SpriteData SpriteData_Create(int width, int height, int row, int column, float alpha) {
	static SpriteData newSprite;
	newSprite.width = width;
	newSprite.height = height;
	newSprite.row = row;
	newSprite.column = column;
	newSprite.alpha = alpha;
	return newSprite;
}

/*Updates data of the Sprite, mainly used for changing size of the sprite dynamically*/
void SpriteData_Update(SpriteData *sprite, int width, int height, float alpha) {
	sprite->width = width;
	sprite->height = height;
	sprite->alpha = alpha;
}

/*
* Sprite_Draw takes in a 'Spritesheet' as a source,
* the column and row of the wanted Sprite from the Spritesheet
* Return nothing
* Uses: Animation_Animate(), Any place that needs to draw a sprite from a spritesheet
* Sub-uses: NIL
*/
void Sprite_Draw(Spritesheet sheet, SpriteData sprite, int xPos, int yPos, int faceX, int faceY) {
	
	int leftmostPixel = sprite.row * sheet.spriteWidth;
	int topMostPixel = sprite.column * sheet.spriteHeight;
	int rightMostPixel = leftmostPixel + sheet.spriteWidth;
	int bottomMostPixel = topMostPixel + sheet.spriteHeight;
	CP_Image_DrawSubImage(sheet.source, (float)xPos + 800, (float)yPos + 450, (float)sprite.width * faceX, (float)sprite.height * faceY,
		(float)leftmostPixel, (float)topMostPixel, (float)rightMostPixel, (float)bottomMostPixel, sprite.alpha);
}