/*---------------------------------------------------------------
  File: popup.c
  Project: GAM100, Team ChocoMochiPie
  Author: Breanne
  Purpose: pop up

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "cprocessing.h"
#include "popup.h"
#include "../CMP_Settings_Pak.h"

void OpenControlsPopUp(void) {
    isPopUpActive = true;
}

void CloseControlsPopUp(void) {
    isPopUpActive = false;
}
