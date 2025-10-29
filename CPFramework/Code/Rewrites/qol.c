#pragma once

#include "cprocessing.h"

CP_Vector GetMousePosition(void) 
{
	return CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
}

float DeltaTime() {
	return CP_System_GetDt();
}

float ElapsedTimeSeconds() 
{
	return CP_System_GetSeconds();
}

float ElapsedTimeMiliseconds() 
{
	return CP_System_GetMillis();
}

int GetScreenHorizontalSize(void) 
{
	return 1600;
}

int GetScreenVerticalSize(void) 
{
	return 900;
}