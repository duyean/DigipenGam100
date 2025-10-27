#pragma once

typedef struct {
	float currentPositionX;
	float currentPositionY;
	int isMoving, isInteracting;
	int faceDirection;
}Player;

typedef enum {
	IDLE, MOVING, INTERACTING
} PlayerState;

void InitPlayer(Player *player);
void DrawPlayer(Player *player);
void PlayerInput(Player* player);
void MovePlayer(Player* player);
void PlayerMovement(int direction, Player* player);

static void PlayerStateMachine(Player* player);
static void PlayerStateLogic(Player* player);
