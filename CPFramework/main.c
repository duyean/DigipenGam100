#include "cprocessing.h"
#include "utils.h"

int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, game_update, game_exit);
	InitUtils();
	SetScene(Intro);
	
	CP_Engine_Run(1);
	return 0;
}

//TEST COMMENT FOR GITHUB UPDATE CHECKING PURPOSES (Can delete at any time :D) test edit