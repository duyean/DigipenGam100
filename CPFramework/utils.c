#include "Code/CMP_Scene_Pak.h"

void (*transitionToSceneFunc) (SceneEnum);
void InitUtils(void) {transitionToSceneFunc = SetScene;}

//I've cleaned up all the functions and organised them -day hehehe