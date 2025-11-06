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
SpriteData SpriteData_Create(int width, int height, int row, int column) {
	static SpriteData newSprite;
	newSprite.width = width;
	newSprite.height = height;
	newSprite.row = row;
	newSprite.column = column;
	return newSprite;
}

/*
* Sprite_Draw takes in a 'Spritesheet' as a source,
* the column and row of the wanted Sprite from the Spritesheet
* Return nothing
* Uses: Animation_Animate(), Any place that needs to draw a sprite from a spritesheet
* Sub-uses: NIL
*/
void Sprite_Draw(Spritesheet sheet, SpriteData sprite, int xPos, int yPos, int flipX, int flipY) {
	
	int leftmostPixel = sprite.row * sheet.spriteWidth;
	int topMostPixel = sprite.column * sheet.spriteHeight;
	int rightMostPixel = leftmostPixel + sheet.spriteWidth;
	int bottomMostPixel = topMostPixel + sheet.spriteHeight;

	CP_Image_DrawSubImage(sheet.source, (float)xPos + 800, (float)yPos + 450, (float)sprite.width * flipX, (float)sprite.height * flipY,
		(float)leftmostPixel, (float)topMostPixel, (float)rightMostPixel, (float)bottomMostPixel, 255);
}