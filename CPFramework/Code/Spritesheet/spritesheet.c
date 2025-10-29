#include "spriteClass.h"
#include <stdio.h>

/*
* Uses the CP_Image as a source, the width and height of Each Sprite
* Return: Initialized Spritesheet
* Uses: DrawSprite(), CreateAnimation()
* Sub-uses: Animate->Animation
*/
Spritesheet CreateSpritesheet(CP_Image source, int w, int h) {
	Spritesheet sheet;
	sheet.source = source;
	sheet.width = CP_Image_GetWidth(source);
	sheet.height = CP_Image_GetHeight(source);
	sheet.spriteWidth = w;
	sheet.spriteHeight = h;

	return sheet;
}

/*
* DrawSprite takes in a 'Spritesheet' as a source,
* the column and row of the wanted Sprite from the Spritesheet
* Return nothing
* Uses: Animate(), Any place that needs to draw a sprite from a spritesheet
* Sub-uses: NIL
*/
void DrawSprite(Spritesheet sheet, int column, int row, int x, int y, int flipX, int flipY) {
	int horizontal = sheet.width / sheet.spriteWidth;
	int vertical = sheet.height / sheet.spriteHeight;

	int leftmostPixel = column * sheet.spriteWidth;
	int topMostPixel = row * sheet.spriteHeight;
	int rightMostPixel = leftmostPixel + sheet.spriteWidth;
	int bottomMostPixel = topMostPixel + sheet.spriteHeight;

	CP_Image_DrawSubImage(sheet.source, (float)x, (float)y, (float)sheet.spriteWidth * flipX, (float)sheet.spriteHeight * flipY,
		(float)leftmostPixel, (float)topMostPixel, (float)rightMostPixel, (float)bottomMostPixel, 255);
}