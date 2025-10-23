#include "cprocessing.h"
#include "utils.h"
#include <stdio.h>
#include "intro.h"

CP_Image digipen, team;
int transitionState, openTransition;
float transition = 0;

void intro_init(void) {
	CP_System_SetWindowSize(1600, 900);
	digipen = CP_Image_Load("./Assets/DigiPen_Singapore_WEB_RED.png");
	team = CP_Image_Load("./Assets/ChocoMochiPie.png");
	openTransition = 1;
}

void intro_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	if (openTransition == 1) {
		switch (transitionState)
		{
		case 0:
			transition += .5f * CP_System_GetDt();
			int alpha = CP_Math_LerpInt(0, 255, transition);
			alpha = CP_Math_ClampInt(alpha, 0, 255);
			CP_Image_Draw(digipen, 800, 450, (float)CP_Image_GetWidth(digipen), (float)CP_Image_GetHeight(digipen), alpha);
			if (alpha >= 255) {
				transitionState = 1;
				printf("Transition state 0 completed\n");
			}
			break;
		case 1:
			transition -= .5f * CP_System_GetDt();
			alpha = CP_Math_LerpInt(0, 255, transition);
			alpha = CP_Math_ClampInt(alpha, 0, 255);
			CP_Image_Draw(digipen, 800, 450, (float)CP_Image_GetWidth(digipen), (float)CP_Image_GetHeight(digipen), alpha);
			if (alpha <= 0) {
				transitionState = 2;
				printf("Transition state 1 completed\n");
			}
			break;
		case 2:
			transition += .5f * CP_System_GetDt();
			alpha = CP_Math_LerpInt(0, 255, transition);
			alpha = CP_Math_ClampInt(alpha, 0, 255);
			CP_Image_Draw(team, 800, 450, (float)CP_Image_GetWidth(team), (float)CP_Image_GetHeight(team), alpha);
			if (alpha >= 255) {
				transitionState = 3;
				printf("Transition state 2 completed\n");
			}
			break;
		case 3:
			transition -= .5f * CP_System_GetDt();
			alpha = CP_Math_LerpInt(0, 255, transition);
			alpha = CP_Math_ClampInt(alpha, 0, 255);
			CP_Image_Draw(team, 800, 450, (float)CP_Image_GetWidth(team), (float)CP_Image_GetHeight(team), alpha);
			if (alpha <= 0) {
				printf("Transition state 3 completed\n");
				openTransition = 0;
				StartTransition();
			}
			break;
		default:
			break;
		}

		if (CP_Input_KeyDown(KEY_SPACE)) {
			StartTransition();
		}
	}
	TransitionFadeOut(2.f, MAIN);
}

void intro_exit(void) {

}