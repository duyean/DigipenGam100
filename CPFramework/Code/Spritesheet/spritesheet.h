#pragma once

#include "spriteClass.h" //required for Spritesheet type

/*Creates data the will contain the Loaded Image Size of a Spritesheet, and Dimensions of Each Sprite*/
Spritesheet Spritesheet_Create(CP_Image source,int spriteWidth,int spriteHeight);

/*Creates data the will contain the Drawn Size of the Sprite, and the Row and Column within a Spritesheet*/
SpriteData SpriteData_Create(int width, int height, int row, int column, float alpha);

/*Draws the Sprite, wanted from a Spritesheet and the Drawn Dimensions, at the wanted position and whether it's flipped on the X/Y Axis*/
void Sprite_Draw(Spritesheet sheet, SpriteData sprite, int xPos, int yPos, int faceX, int faceY);

/*Updates data of the Sprite, mainly used for changing size of the sprite dynamically*/
void SpriteData_Update(SpriteData* sprite, int width, int height, float alpha);