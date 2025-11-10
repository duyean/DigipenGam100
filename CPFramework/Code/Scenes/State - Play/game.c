#include "cprocessing.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Player_Pak.h"
#include "../../CMP_Interactable_Pak.h"
#include "../../CMP_Room_Pak.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../Characters/Monster A/monsterBaby.h"

#define INTERACTABLES_COUNT 2
#define ROOM_COUNT 5

#define CENTER_ROOM_INDEX 2

#define RENDER_RANGE 1600

CP_Color background;
Player player;
Camera* camera;
float playerX = 0, playerY = 0;
float lastPlayerX = 0, lastPlayerY = 0;

Interactable *interactablesArray[INTERACTABLES_COUNT];

Interactable oilBlob;
Spritesheet oilSpritesheet;
SpriteData oilFrames[4];
CP_Image oilImage;
Animation oilAnimation;

CP_Image lockerImage;
Interactable locker;
Spritesheet lockerSheet;
SpriteData lockerSprites[2];
Animation lockerAnimation;

CP_Vector worldCenterPosition;

//Test Background Sprites
Room* roomList[ROOM_COUNT];
Room r1, r2, r3, r4, r5;

CP_Image Bg1_i[3];
Spritesheet Bg1_ss[3];
SpriteData Bg1_sd[3];

CP_Image Bg2_i[3];
Spritesheet Bg2_ss[3];
SpriteData Bg2_sd[3];

CP_Image Bg3_i[3];
Spritesheet Bg3_ss[3];
SpriteData Bg3_sd[3];

//Just to reduce the printf occurence
float lastFrameTime = 0;


/*UPDATE THE ADDRESS HANDLING FOR INTERACTABLES*/

/*Functions here are for testing and can be removed for FINAL*/
void InitialiseInteractables(void);
void LockerTest(void);
void InitialiseRooms(void);

extern CP_Sound mainMenuMusic;
extern CP_Sound gameplayMusic;
extern CP_Sound soundEffects;

extern float masterVolume;
extern float effectiveBGM;
extern float effectiveSFX;

CP_Image vignette;
void game_init(void) {
	vignette = CP_Image_Load("./Assets/Vignette.png");
	background = CP_Color_Create(150, 150, 150, 255);
	Player_Initialise(&player);
	initializeBaby();
	setPlayerRef(&player);
	CreateCamera(&camera, player.currentPositionX, player.currentPositionY);

	worldCenterPosition = CP_Vector_Set(CP_System_GetWindowWidth() * .5f, CP_System_GetWindowHeight() * .5f);

	InitialiseInteractables();

	//Test Background Sprites
	InitialiseRooms();
}

void game_update(void) {
	CP_Vector centerOfScreen = CP_Vector_Set(CP_System_GetWindowWidth() * .5f, CP_System_GetWindowHeight() * .5f);
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

	CP_Graphics_DrawRect(centerOfScreen.x - playerX, centerOfScreen.y - playerY, 50, 50);

	//clear console cause holy shit i get headache trying to read -day
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	for (int i = 0; i < ROOM_COUNT + 2; i++)
	{
		int pX = player.currentPositionX, pY = player.currentPositionY;
		int sightCheckP1 = pX + RENDER_RANGE, sightCheckP2 = pX - RENDER_RANGE;
		if (i < ROOM_COUNT)
		{
			int sightCheckR = roomList[i]->xPos;
			//only load rooms in view (to save space!!!)
			if (sightCheckR <  sightCheckP1 && sightCheckR > sightCheckP2)
			{
				Room_Load(roomList[i], 3, player);
				printf("Loading Room %d\n", i);
			}
		}
		//edge case left room loop to right.
		else if (i == ROOM_COUNT)
		{
			int sightCheckR = (roomList[0]->xPos) - 1600;

			if (sightCheckR <  sightCheckP1 && sightCheckR > sightCheckP2)
			{
				Room_LoadO(roomList[ROOM_COUNT-1], 3, player, -(ROOM_COUNT / 2 + 1) * 1600);
				printf("Loading Room: LOOP LEFT\n");
				if (pX < -(ROOM_COUNT/2+1) * 1600)
				{
					player.currentPositionX += ROOM_COUNT * 1600;
					//TeleportMonsterRoom((ROOM_COUNT * 1600));
					printf("Looping Left to Right\n");
				}
			}
		}
		//edge case rignt room loop to left.
		else if (i > ROOM_COUNT)
		{
			int sightCheckR = roomList[ROOM_COUNT-1]->xPos + 1600;
			if (sightCheckR <  sightCheckP1 && sightCheckR > sightCheckP2)
			{
				Room_LoadO(roomList[0], 3, player, (ROOM_COUNT / 2 + 1) * 1600);
				printf("Loading Room: LOOP RIGHT\n");
				if (pX > (ROOM_COUNT/2 + 1) * 1600)
				{
					player.currentPositionX -= ROOM_COUNT * 1600;
					//TeleportMonsterRoom(-1 * (ROOM_COUNT * 1600));
					printf("Looping Right to Left\n");
				}
			}
		}
	}
	printf("Player X Position: %.3f\n", player.currentPositionX);

	for (int i = 0; i < INTERACTABLES_COUNT; i++) {
		Interactable_Update(interactablesArray[i], interactablesArray[i]->xPosition - playerX, interactablesArray[i]->yPosition - playerY);
	}



	Player_Update(&player);
	UpdateMonsterBaby();
	/*TO BE UPDATED: SLOT FUNCTION FOR CURRENT ROOM - J*/
	Player_CheckInteractables(interactablesArray, INTERACTABLES_COUNT);

	// Calculate player movement delta (velocity) since last frame
	playerX = player.currentPositionX;
	playerY = player.currentPositionY;
	float dx = playerX - lastPlayerX;  // playerDX: horizontal movement from last frame
	float dy = playerY - lastPlayerY;  // playerDY: vertical movement from last frame
	lastPlayerX = playerX;
	lastPlayerY = playerY;

	UpdateCamera(&camera, player.currentPositionX, player.currentPositionY, dx, dy, 0.1f); //test case, please edit later. Read camera.c for more info. -day

	/*
	using parallex code here for background layers later
	if you can't do it then say i guess. 
	I think I made it ok to follow.
													-day
	*/

	// Draw a red box in the center of the screen
	CP_Settings_Fill(CP_Color_Create(255, 100, 255, 255));

	TransitionFadeIn(.5f, 0, 0, 0, 255);
	TransitionFadeOut(.5f, MAIN);

	CP_Image_Draw(vignette, 800, 450, 1600, 900, 170);
	/*if (lastFrameTime <= CP_System_GetSeconds()) {
		lastFrameTime = CP_System_GetSeconds() + CP_System_GetDt();
		printf("Current Player X Position: %.3f\n", playerX);
	}*/
}

void game_exit(void) {

}

void InitialiseInteractables(void) {
	lockerImage = CP_Image_Load("Assets/LockerSpritesheet.png");
	oilImage = CP_Image_Load("Assets/BlobSprite.png");

	lockerSheet = Spritesheet_Create(lockerImage, CP_Image_GetWidth(lockerImage) / 2, CP_Image_GetHeight(lockerImage));
	lockerSprites[0] = SpriteData_Create(100, 200, 0, 0, 255.f);
	lockerSprites[1] = SpriteData_Create(100, 200, 1, 0, 255.f);
	lockerAnimation = Animation_Create(lockerSheet, lockerSprites, 25.f, 2, 0, 0);
	locker = Interactable_Create(0, 20.f, 100.f, "Locker", lockerSheet, lockerSprites[0], &LockerTest);
	Interactable_AttachAnimation(&locker, lockerAnimation);
	interactablesArray[0] = &locker;

	oilSpritesheet = Spritesheet_Create(oilImage, 514, 514);
	oilFrames[0] = SpriteData_Create(200, 200, 0, 0, 255.f);
	oilFrames[1] = SpriteData_Create(200, 200, 1, 0, 255.f);
	oilFrames[2] = SpriteData_Create(200, 200, 0, 1, 255.f);
	oilFrames[3] = SpriteData_Create(200, 200, 1, 1, 255.f);
	oilAnimation = Animation_Create(oilSpritesheet, oilFrames, 10.f, 4, 1, 1);
	oilBlob = Interactable_Create(300.f, 0.f, 100.f, "Sludge 1", oilSpritesheet, oilFrames[0], &InteractionSludge);
	Interactable_AttachAnimation(&oilBlob, oilAnimation);
	interactablesArray[1] = &oilBlob;
}

void LockerTest(void) {
	InteractionLocker(&locker, &player);
}

void InitialiseRooms(void) {
	Bg1_i[0] = CP_Image_Load("Assets/BG1Back.png");
	Bg2_i[0] = CP_Image_Load("Assets/BG2Back.png");
	Bg3_i[0] = CP_Image_Load("Assets/BG3Back.png");

	Bg1_i[1] = CP_Image_Load("Assets/Ground.png");
	Bg2_i[1] = CP_Image_Load("Assets/Ground.png");
	Bg3_i[1] = CP_Image_Load("Assets/Ground.png");

	Bg1_i[2] = CP_Image_Load("Assets/Ceiling.png");
	Bg2_i[2] = CP_Image_Load("Assets/Ceiling.png");
	Bg3_i[2] = CP_Image_Load("Assets/Ceiling.png");

	for (int i = 0; i < 3; i++)
	{
		Bg1_sd[i] = Bg2_sd[i] = Bg3_sd[i] = SpriteData_Create(1600, 900, 0, 0, 255.f);

		Bg1_ss[i] = Spritesheet_Create(Bg1_i[i], CP_Image_GetWidth(Bg1_i[i]), CP_Image_GetHeight(Bg1_i[i]));
		Bg2_ss[i] = Spritesheet_Create(Bg2_i[i], CP_Image_GetWidth(Bg2_i[i]), CP_Image_GetHeight(Bg2_i[i]));
		Bg3_ss[i] = Spritesheet_Create(Bg3_i[i], CP_Image_GetWidth(Bg3_i[i]), CP_Image_GetHeight(Bg3_i[i]));
	}

	r1 = Room_Create(Bg3_ss, Bg3_sd, 3, -3200, 0, interactablesArray, 0);
	roomList[0] = &r1;
	r2 = Room_Create(Bg1_ss, Bg1_sd,3, -1600, 0, interactablesArray, 0);
	roomList[1] = &r2;
	r3 = Room_Create(Bg2_ss, Bg2_sd,3, 0, 0, interactablesArray, 0);
	roomList[2] = &r3;
	r4 = Room_Create(Bg3_ss, Bg3_sd,3, 1600, 0, interactablesArray, 0);
	roomList[3] = &r4;
	r5 = Room_Create(Bg1_ss, Bg1_sd,3, 3200, 0, interactablesArray, 0);
	roomList[4] = &r5;
	
}