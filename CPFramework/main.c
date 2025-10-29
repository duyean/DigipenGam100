#include "cprocessing.h"
#include "utils.h"
#include "Code/CMP_Scene_Pak.h"

//THIS IS THE STARTING FILE. GENESIS, THE BEGINNING AND THE END
int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, game_update, game_exit);
	InitUtils();
	SetScene(MAIN);
	
	CP_Engine_Run(1);
	return 0;
}