#include "cprocessing.h"
#include "utils.h"
#include "player.h"

CP_Color background;
Player player;

float tX = 0, tY = 0;

void game_init(void) {
	background = CP_Color_Create(150, 150, 150, 255);
	InitPlayer(&player);
}

void game_update(void) {

	if (CP_Input_KeyDown(KEY_A)) {
		tX -= 100.0f * DeltaTime();
	}
	else if (CP_Input_KeyDown(KEY_D)) {
		tX += 100.0f * DeltaTime();
	}

	CP_Settings_ResetMatrix();
	CP_Graphics_ClearBackground(background);
	CP_Matrix translate = CP_Matrix_Translate(CP_Vector_Set(tX, 0));
	CP_Matrix scale = CP_Matrix_Scale(CP_Vector_Set(100, 100));
	CP_Matrix rotate = CP_Matrix_Rotate(0.0f);

	// Combine transform (translate * rotation * scale)
	CP_Matrix transform = CP_Matrix_Multiply(translate, CP_Matrix_Multiply(rotate, scale));
	CP_Settings_ApplyMatrix(translate);
	CP_Settings_ResetMatrix();
	
	PlayerInput(&player);
	MovePlayer(&player);
	DrawPlayer(&player);


	if (CP_Input_KeyReleased(KEY_Q)) {
		StartTransition();
	}

	TransitionFadeIn(.5f, 0, 0, 0, 255);
	TransitionFadeOut(.5f, MAIN);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Graphics_DrawRect(100, 100, 150, 100);
	CP_Graphics_DrawCircle(180, 220, 100);
}

void game_exit(void) {

}