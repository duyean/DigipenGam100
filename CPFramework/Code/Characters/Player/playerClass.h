#pragma once
typedef struct {
	float currentPositionX, currentPositionY;	//Current World Position of the Player
	int currentHealth, maxHealth;				//Current & Max Health of the Player
	float currentStamina, maxStamina;				//Current & Max Stamina
	float currentOil, maxOil;						//Current & Max Oil
	int isMoving, isInteracting;				//Checks for the Player
	int faceDirection;
	int toDraw;
	float movementSpeed;
}Player;