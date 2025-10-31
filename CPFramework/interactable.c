#include <stdio.h>
#include "cprocessing.h"
#include "interactable.h"
#include "player.h"



Interactable CreateInteractable(float xPos, float yPos, Spritesheet sheet, void (*OnInteract)(void)) {
	Interactable newInteractable;
	newInteractable.xPosition = xPos;
	newInteractable.yPosition = yPos;
	newInteractable.spritesheet = sheet;
	newInteractable.OnInteract = OnInteract;
	return newInteractable;
}

void InteractionLocker(void) {
	//Whatever happen to the locker on interaction
}

void InteractionSludge(void) {
	//whatever happens to the sludge on interaction
}