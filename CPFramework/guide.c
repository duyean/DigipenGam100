//#include "utils.h"
//#include <stdio.h>
//#include "cprocessing.h"
//
///*
//* This Program is not meant to be used in the final product of the game.
//* This exists for the devs responible for UI as well as Menu Navigation Management.
//* This program is a form of documentaion and is NOT to be included in the final executable.
//* 
//* How To Read:
//* Each function is named as a guide and have not been made to be run in the game and is mainly
//* used to show how to structure elements such as buttons. Additional comments will be made as to
//* where to include said elements' functions so as to avoid confusion in future implementations.
//*/
//
///*HOW TO CREATE BUTTON AND DRAW BUTTON*/
//
////include "Button.h"
//void ButtonPress(void);
//
////Global to Create Button
//Button button;  //To be declared so as to use it in whole program
//
//float hPos, vPos, width, height;
//int alpha;
//CP_Image imageForButton;
//CP_Color textColor;
//TextTemplate texT;
//
//void HowToCreateButton() {
//	//Init
//
//	/*CreateButton takes in the values for its X & Y Position, Width * Height,
//	the alpha of the button and the Function that is to be executed when pressing the button
//	This function returns the button with all stated values*/
//	button = CreateButton(hPos, vPos, width, height, alpha, &ButtonPress);
//
//	
//	/*AddTextToButton takes in a Created button and adds text that will be displayed with
//	a stated offset in the x and y axis*/
//	button = AddTextToButton(&button, "Sometext", 0, 0);
//
//	/*LoadImage to be used for the button*/
//	imageForButton = CP_Image_Load("./Assets/Some.png");
//
//	/*Create a template to be used for the text*/
//	texT = CreateTextTemplate("filePath for font", textColor);
//
//	//Update
//	DrawButtonUsingImage(imageForButton, &button, texT);
//	//Exit
//
//}
//
//void ButtonPress(void) {
//
//}
//
///*HOW TO CREATE BUTTON AND DRAW BUTTON END*/