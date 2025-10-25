#include "cprocessing.h"
#include "utils.h"
#include "player.h"

CP_Color background;
Player player;

void game_init(void) {
	background = CP_Color_Create(150, 150, 150, 255);
	InitPlayer(&player);
}

void game_update(void) {
	CP_Graphics_ClearBackground(background);
	DrawPlayer(&player);
}

void game_exit(void) {

}