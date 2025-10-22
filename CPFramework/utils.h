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

typedef struct {
	Spritesheet sheet;
	int currentColumnFrame;
	int currentRowFrame;
	int columnSize;
	int rowSize;
	int *columnFrames;
	int *rowFrames;
	float frameDuration;
	float lastFrameTime;
} Animation;

typedef struct {
	CP_Font font;
	CP_Color color;
} TextTemplate;

typedef struct {
	float x, y, w, h;
	int a;
	char* text;
	float textOffsetX, textOffsetY;
}Button;

void InitUtils(void);
void SetScene(SceneEnum scene);
void TransitionFadeIn(float transitionSpeed, int r, int g, int b, int a);
void TransitionFadeOut(float, SceneEnum);
void StartTransition(void);
int GetScreenHorizontalSize(void);
int GetScreenVerticalSize(void);

CP_Image DrawButtonUsingImage(CP_Image loadedImage, Button* button, TextTemplate texT);
Button CreateButton(float x, float y, float w, float h, int a);
Button AddTextToButton(Button* button, char* text, int xOffset, int yOffset);
TextTemplate CreateTextTemplate(char* font, CP_Color color);
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

Spritesheet CreateSpritesheet(CP_Image source, int w, int h);
void DrawSprite(Spritesheet sheet, int xRow, int rRow, int x, int y);
Animation CreateAnimation(Spritesheet sheet, int cFrames[10], int rFrames[10], float animationSpeed, int cSize, int rSize);
void Animate(Animation *animation, float x, float y);

CP_Vector GetMousePosition(void);

float DeltaTime();
float ElapsedTimeSeconds();
float ElapsedTimeMiliseconds();