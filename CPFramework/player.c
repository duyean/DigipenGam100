#include "cprocessing.h"
#include "player.h"
#include "utils.h"

#define ArraySize(a) (sizeof(a)/sizeof(a[0]))

CP_Image characterSheetImage;
Spritesheet characterSheet;
Animation characterAnimation;
int rowFrames[4] = { 0,1,0,1 };
int columnFrames[4] = { 0,0,1,1 };
float frameDuration = 15.f;

float movementSpeed = 100.f;

PlayerState currentPlayerState = IDLE;

void InitPlayer(Player *player) {
	characterSheetImage = CP_Image_Load("./Assets/WalkCycleSpriteSheet.png");
	characterSheet = CreateSpritesheet(characterSheetImage, 258, 258);
	characterAnimation = CreateAnimation(characterSheet, columnFrames, rowFrames, frameDuration,
		ArraySize(columnFrames), ArraySize(rowFrames));

	player->currentPositionX = 800;
	player->currentPositionY = 450;
	player->faceDirection = 1;
	player->isInteracting = player->isMoving = 0;
}

void DrawPlayer(Player *player) {
	PlayerStateLogic(player);
	PlayerStateMachine(player);
}

void MovePlayer(Player* player) {
	PlayerMovement(player->faceDirection, player);
}

static void PlayerMovement(int direction, Player *player) {
	player->currentPositionX += direction * movementSpeed * DeltaTime();
}

static void PlayerStateMachine(Player *player) {
	switch (currentPlayerState){
	case IDLE:
		DrawSprite(characterSheet, 1, 0, player->currentPositionX, 450);
		break;
	case MOVING:
		Animate(&characterAnimation, player->currentPositionX, 450);
		break;
	case INTERACTING:
		break;
	default:
		break;
	}
}

static void PlayerStateLogic(Player *player) {
	currentPlayerState = player->isInteracting ? INTERACTING :
		(player->isMoving ? MOVING : IDLE);
}

void PlayerInput(Player *player) {
	if (CP_Input_KeyDown(KEY_D)) {
		player->faceDirection = 1;
		player->isMoving = 1;
	}
	else if (CP_Input_KeyDown(KEY_A)) {
		player->faceDirection = -1;
		player->isMoving = 1;
	}
	else {
		player->faceDirection = 0;
		player->isMoving = 0;
	}
}