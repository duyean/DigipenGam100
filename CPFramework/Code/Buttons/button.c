#include <stdio.h>
#include <math.h>
#include "cprocessing.h"
#include "../CMP_Button_Pak.h"
#include "../CMP_Core_Pak.h" //required for GetMousePosition()


int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	//simplified for you hehe, no need to create extra variables or ternary/if-else! -day
	return abs(area_center_x - click_x) <= area_width / 2 && abs(area_center_y - click_y) <= area_height / 2;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	//if you're going to import math.h, might as well use the functions, right? -day
	return sqrt(pow(circle_center_x - click_x, 2)) + sqrt(pow(circle_center_y - click_y,2)) <= diameter/2;
}

/*
* Makes use of a loaded CP_Image and Button Pointer and a TextTemplate
* Returns: CP_Image
* Uses: Drawing Button with an Image of Drawing Shapes
*/
CP_Image DrawButtonUsingImage(CP_Image loadedImage, Button *button, TextTemplate texT) {
	if (loadedImage == NULL) return loadedImage;

	// jelly addition for button hover/press 'animation'
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	// checks if the mouseX and mouseY is within the boundaries of the button
	CP_BOOL IsHovering = (mouseX > button->x - button->w / 2 && mouseX < button->x + button->w / 2 && mouseY > button->y - button->h / 2 && mouseY < button->y + button->h / 2);
	CP_Color ButtonTint = CP_Color_Create(255, 255, 255, 255); // adds a black overlay because this will be used for the actual tinting

	if (IsHovering && CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		ButtonTint = CP_Color_Create(100, 100, 100, 255);
	}
	else if (IsHovering) {
		ButtonTint = CP_Color_Create(180, 180, 180, 255);
	}

	CP_Settings_Tint(ButtonTint); // this wan is where it tints, gotta draw after the tint if not its just gonna be BUHLACK

	CP_Image_Draw(loadedImage, button->x, button->y, button->w, button->h, button->a);

	CP_Settings_Tint(CP_Color_Create(255, 255, 255, 255)); // this wan reset tint after drawing

	// mr jerome's amazing code
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

	// this wan handles the click event 
	if (CP_Input_MouseClicked() && IsHovering)
	{
		if (button->OnButtonPress != NULL) {
			button->OnButtonPress();
		}
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