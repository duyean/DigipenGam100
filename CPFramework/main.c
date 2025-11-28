#include "cprocessing.h"
#include "utils.h"
#include "Code/CMP_Scene_Pak.h"

//THIS IS THE STARTING FILE. GENESIS, THE BEGINNING AND THE END
int main(void)
{
	InitialiseUtilities();
	SetScene(INTRO);
	
	CP_Engine_Run(1);
	return 0;
}