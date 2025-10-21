#pragma once

typedef enum 
{
	Intro, Main, Settings, Game, Pause
}SceneEnum;

static char* sceneNames[] = { "Intro", "Main", "Settings", "Game", "Pause" };

typedef struct {
	CP_Image source;
	int width;
	int height;
	int spriteWidth;
	int spriteHeight;
}Spritesheet;

void InitUtils(void);
void SetScene(SceneEnum scene);
void TransitionFadeIn(float transitionSpeed, int r, int g, int b, int a);
void TransitionFadeOut(float, SceneEnum);
void StartTransition(void);
int GetScreenHorizontalSize(void);
int GetScreenVerticalSize(void);

CP_Image ButtonUsingImage(CP_Image loadedImage, float x, float y, float w, float h, int a);
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

Spritesheet CreateSpritesheet(CP_Image source, int w, int h);
void DrawSprite(Spritesheet sheet, int xRow, int rRow, int x, int y);

CP_Vector GetMouseClickPosition(void);