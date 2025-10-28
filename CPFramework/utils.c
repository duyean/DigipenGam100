#include "cprocessing.h"
#include "utils.h"
#include "Code/Scenes/State - Main Menu/mainmenu.h"
#include "game.h"
#include "settingsmenu.h"
#include "intro.h"
#include <stdio.h>
#include <math.h>

int isFadeIn = 0;
int isFadeOut = 0;
float transitionAlpha = 0;
void (*transitionToSceneFunc) (SceneEnum);
SceneEnum currentScene;

int IsDebug = 0;

//Initialize any utils, will be ran at main.c
void InitUtils(void) {
	transitionToSceneFunc = SetScene;
}

//### SCENE RELATED ###

/*
* SetScene takes in a sceneEnum
* Uses: Changes Scene
* Sub-uses: Used in main.c and FadeInOut Functions
*/
void SetScene(SceneEnum scene) {
	printf("\nChanging from Scene: %s\n", sceneNames[currentScene]);
	currentScene = scene;
	printf("Changing to Scene: %s\n\n", sceneNames[currentScene]);
	switch (scene){
	case INTRO:
		CP_Engine_SetNextGameState(intro_init, intro_update, intro_exit);
		break;
	case MAIN:
		CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
		break;
	case SETTINGS:
		CP_Engine_SetNextGameState(settings_menu_init, settings_menu_update, settings_menu_exit);
		break;
	case GAME:
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		break;
	default:
		printf("DEFAULT SET SCENE USED!!! CHECK FOR SWITCH FALL! OR NON-EXISTING ENUM!");
		CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
		break;
	}
}

/*
* TransitionFadeIn takes speed of the transition, RGBA of the transition colour
* Return: NIL
* Uses: Used to begin transition between scenes
* Fade from 0 to full colour alpha screen
* Sub-uses: NIL
*/
void TransitionFadeOut(float transitionSpeed, SceneEnum scene) {
	if (isFadeOut == 0) return;
	CP_Settings_NoStroke();
	transitionAlpha += transitionSpeed * DeltaTime();
	int alpha = CP_Math_LerpInt(0, 255, transitionAlpha);
	alpha = CP_Math_ClampInt(alpha, 0, 255);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, alpha));
	CP_Graphics_DrawRect(800, 450, 1600, 900);
	if (alpha >= 255) {
		isFadeOut = 0;
		isFadeIn = 1;
		printf("Fade Out Completed, Transition to Scene: %s\n", sceneNames[scene]);
		transitionToSceneFunc(scene);
	}
}

/*
* TransitionFadeIn takes speed of the transition, RGBA of the transition colour
* Return: NIL
* Uses: Should Only be used after a fullscreen effect
* Fade from full colour alpha screen to 0
* Sub-uses: NIL
*/
void TransitionFadeIn(float transitionSpeed, int r, int g, int b, int a) {
	if (isFadeIn == 0) return;
	CP_Settings_NoStroke();
	transitionAlpha -= transitionSpeed * DeltaTime();
	int alpha = CP_Math_LerpInt(0, a, transitionAlpha);
	alpha = CP_Math_ClampInt(alpha, 0, a);
	CP_Settings_Fill(CP_Color_Create(r, g, b, alpha));
	CP_Graphics_DrawRect(800, 450, 1600, 900);
	if (alpha <= 0) {
		printf("Fade In Completed\n");
		isFadeIn = 0;
	}
}

//Manually Start the transition
void StartTransition(void) {
	if (isFadeOut == 1 || isFadeIn == 1) return;
	isFadeOut = 1;
}

int GetScreenHorizontalSize(void) {
	return 1600;
}

int GetScreenVerticalSize(void) {
	return 900;
}

//### SCENE RELATED END ###



//### USER INTERFACE RELATED ###

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	int withinX = click_x >= area_center_x - area_width / 2 && click_x <= area_center_x + area_width / 2;
	int withinY = click_y >= area_center_y - area_height / 2 && click_y <= area_center_y + area_height / 2;
	if (withinX && withinY) {
		return 1;
	}
	else {
		return 0;
	}
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	float radius = diameter / 2;
	return fabs((circle_center_x - click_x) * (circle_center_x - click_x) 
		+ (circle_center_y - click_y) * (circle_center_y - click_y)) 
		<= radius * radius;
}

/*
* Makes use of a loaded CP_Image and Button Pointer and a TextTemplate
* Returns: CP_Image
* Uses: Drawing Button with an Image of Drawing Shapes
*/
CP_Image DrawButtonUsingImage(CP_Image loadedImage, Button *button, TextTemplate texT) {
	if (loadedImage == NULL) return loadedImage;
	CP_Image_Draw(loadedImage, button->x, button->y, button->w, button->h, button->a);
	if (button->text != NULL || button->text != "") {
		CP_Settings_Fill(texT.color);
		CP_Settings_TextSize(35.0f);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Font_DrawText(button->text, button->x + button->textOffsetX, button->y + button->textOffsetY);
	}
	if (!CP_Input_MouseClicked()) return loadedImage;
	if (IsAreaClicked(button->x, button->y, button->w, button->h, GetMousePosition().x, GetMousePosition().y)) {
		if(button->OnButtonPress != NULL) button->OnButtonPress();
	}
	return loadedImage;
}

/*
* Takes in position and size in floats, and alpha in int, and Pointer Function of the button
* Returns: Initialized Button
* Uses: To set basic values a Button to be used later
*/
Button CreateButton(float x, float y, float w, float h, int a, void* buttonFunc) {
	Button newButton;
	newButton.x = x;
	newButton.y = y;
	newButton.w = w;
	newButton.h = h;
	newButton.a = a;
	newButton.OnButtonPress = buttonFunc;
	return newButton;
}

/*
* Takes in Button Pointer, String, Positional offset using ints
* Returns: Text Initialized Button
* Uses: To set the text for button and the offset of the text within the button
*/
Button AddTextToButton(Button* button, char* text, int xOffset, int yOffset) {
	button->text = text;
	button->textOffsetX = xOffset;
	button->textOffsetY = yOffset;
	return *button;
}

/*
* Takes in filePath of the font and the CP_Color
* Returns: Initialized TextTemplate
* Uses: To keep the font and colour as a template for later use
*/
TextTemplate CreateTextTemplate(char* font, CP_Color color) {
	TextTemplate newTT;
	newTT.font = CP_Font_Load(font);
	newTT.color = color;
	return newTT;
}

//### USER INTERFACE RELATED ###



//### SPRITE RELATED ###

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

/*
* Uses Init 'Spritesheet', the array format of each frame in order, the time between frames, and size each dimension
* Return: Initialized Animation
* Uses: To Create references to animation
* Sub-uses: NIL
*/
Animation CreateAnimation(Spritesheet sheet, int cFrames[10], int rFrames[10], float animationSpeed, int cSize, int rSize) {
	Animation newAnimation;
	newAnimation.frameDuration = animationSpeed;
	newAnimation.columnFrames = cFrames;
	newAnimation.rowFrames = rFrames;
	newAnimation.currentColumnFrame = 0;
	newAnimation.currentRowFrame = 0;
	newAnimation.columnSize = cSize;
	newAnimation.rowSize = rSize;
	newAnimation.sheet = sheet;
	return newAnimation;
}

/*
* Animate takes in a 'Animation' Pointer as a source, the x and y position of the animation and the elapsedTime of the game
* Returns: NIL
* Uses: To Animate the passed in animation of whatever game object
* Sub-uses: NIL
*/
void Animate(Animation *animation, float x, float y, int flipX, int flipY) {
	float currentTime = ElapsedTimeSeconds();
	if (animation->lastFrameTime <= currentTime) {
		animation->lastFrameTime = currentTime + animation->frameDuration * DeltaTime();

		animation->currentColumnFrame++;
		animation->currentRowFrame++;

		if (animation->currentRowFrame >= animation->rowSize) {
			animation->currentRowFrame = 0;
		}
		if (animation->currentColumnFrame >= animation->columnSize) {
			animation->currentColumnFrame = 0;
		}
	}

	int rowFrame = animation->rowFrames[animation->currentRowFrame];
	int columnFrame = animation->columnFrames[animation->currentColumnFrame];

	DrawSprite(animation->sheet, rowFrame, columnFrame, x, y, flipX, flipY);
}

//### SPRITE RELATED END ###



//### INPUT RELATED ###

/*
* GetMouseClickPosition takes in nothing
* Return CP_Vector with the X and Y Mouse position
* Uses: To be used after a MouseDown check to find position but
* can be used for other functions
* Sub-uses: NIL
*/
CP_Vector GetMousePosition(void) {
	return CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
}

//### INPUT RELATED END ###



//### TIME RELATED ###

float DeltaTime() {
	return CP_System_GetDt();
}

float ElapsedTimeSeconds() {
	return CP_System_GetSeconds();
}

float ElapsedTimeMiliseconds() {
	return CP_System_GetMillis();
}

//### TIME RELATED END ###



//### DEBUG RELATED ###

void ShowDebugInfo(void) {
	CP_Settings_TextSize(15.0f);
	CP_Font_DrawText("Debug Info:", 1500, 800);
	ShowCurrentScene();
}

static void ShowCurrentScene(void) {
	CP_Font_DrawText("Current Scene: ", 1480, 820);
	CP_Font_DrawText(sceneNames[currentScene], 1540, 820);
}

int IsDebugging(void) {
	return IsDebug;
}

void ToggleDebug(void) {
	IsDebug = IsDebug == 1 ? 0 : 1;
}

//### DEBUG RELATED END ###