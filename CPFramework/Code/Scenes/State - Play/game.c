#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "game.h"
#include "../../CMP_Core_Pak.h"
#include "../../CMP_Scene_Pak.h"
#include "../../CMP_Player_Pak.h"
#include "../../CMP_Interactable_Pak.h"
#include "../../CMP_Room_Pak.h"
#include "../../CMP_Audio_Pak.h"
#include "../../CMP_Settings_Pak.h"
#include "../../CMP_Monster_Pak.h"
#include "../../CMP_Dialogue_Pak.h"
#include "../../Dbg/dbg.h"


enum { INTERACTABLES_COUNT = 3};
#define RENDER_RANGE 1600
#define MAX_ROOMS 20

CP_Color background;
Player player;
Camera* camera;
float playerX = 0, playerY = 0;
float lastPlayerX = 0, lastPlayerY = 0;

Interactable *interactablesArray_a[INTERACTABLES_COUNT];
Interactable *interactablesArray_b[INTERACTABLES_COUNT];
Interactable *interactablesArray_c[INTERACTABLES_COUNT];

Interactable oilBlobTest;
Interactable doorTest;
Interactable liftTest;

CP_Vector worldCenterPosition;

//room shit
unsigned short int roomCount = 5, centerRoomIndex = 2;

//Test Background Sprites
Room* roomList[MAX_ROOMS], r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20;

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

// settings menu
bool isGamePaused = false;
Button resumeButton, quitButton, settingsButton;
TextTemplate pauseTextTemplate;
CP_Image buttonBG, settingsButtonBG;
SceneEnum sceneChange;
Slider BGMSlider, SFXSlider, masterSlider;
CP_Color knobColor;

// dialogue stuff
static DialogueSystem ds;   // global dialogue system
static DialogueLine* lines; // loaded dialogue lines
static int lineCount = 0;
static int dialogueJustStarted = 0;

CP_Image vignette;
float FadeIn;

CP_Image youDiedImage;
SceneEnum nextScene;

int DEBUG_ENABLED = 0;

void InitialiseInteractables(void);
void LockerTest(void);
void LiftTest(void);
void InitialiseRooms(void);
void Room_Update(void);

void game_init(void) {
	//I HATE YOU IM JUST GONNA HARDCODE FUCK YOU -day
	roomList[0] = &r1; 	roomList[1] = &r2; roomList[2] = &r3; roomList[3] = &r4; roomList[4] = &r5; roomList[5] = &r6; 	roomList[6] = &r7; roomList[7] = &r8; roomList[8] = &r9; roomList[9] = &r10;roomList[10] = &r11; roomList[11] = &r12; roomList[12] = &r13; roomList[13] = &r14; roomList[14] = &r15; roomList[15] = &r16; roomList[16] = &r17; roomList[17] = &r18; roomList[18] = &r19; roomList[19] = &r20;
	//oh my god it is endless. Just like my loathing for you and it's entirety. 
	//this is for a debugging we might not even have a time to use.

	buttonBG = CP_Image_Load("./Assets/MainMenuButton.png");
	settingsButtonBG = CP_Image_Load("./Assets/SettingsButton.png");

	//dialogueBox = CP_Image_Load("./Assets/DialogueBox.png");
	//dialogueLady = CP_Image_Load("./Assets/DialogueLady.png");

	pauseTextTemplate = CreateTextTemplate("./Assets/Fonts/CaviarDreams_Bold.ttf", CP_Color_Create(255, 255, 255, 255));
	CP_Font_Set(pauseTextTemplate.font);

	// which is basically the back button
	resumeButton = CreateButton(500, 400, 480, 60, 255, &ResumeGame);
	resumeButton = AddTextToButton(&resumeButton, "Resume", -100, 0);

	quitButton = CreateButton(500, 500, 480, 60, 255, &QuitGame);
	quitButton = AddTextToButton(&quitButton, "Main Menu", -100, 0);

	settingsButton = CreateButton(1500, 100, 60, 60, 255, &PauseGame);
	settingsButton = AddTextToButton(&settingsButton, "", -100, 0);

	SliderValues(&masterSlider, 900, 400);
	SliderValues(&BGMSlider, 900, 500);
	SliderValues(&SFXSlider, 900, 600);

	vignette = CP_Image_Load("./Assets/Vignette.png");
	youDiedImage = CP_Image_Load("./Assets/youdiedtest.png");
	background = CP_Color_Create(150, 150, 150, 255);
	Player_Initialise(&player);
	InitializeRedBaby();
	InitializeBaby();

    SpawnMonster(RED_BABY, 2, -3200.f, 3200.f); //Set room min and max
	SpawnMonster(BABY, 2, -3200.f, 3200.f); //Set room min and max
	SetPlayerRef(&player);
	CreateCamera(&camera, player.currentPositionX, player.currentPositionY);

	worldCenterPosition = CP_Vector_Set(CP_System_GetWindowWidth() * .5f, CP_System_GetWindowHeight() * .5f);

	InitialiseInteractables();

	//Test Background Sprites
	InitialiseRooms();

	lines = LoadDialogueFromTextFile("./Assets/Floor_Enter_Default_a.txt", &lineCount);
	if (!lines) {
		printf("failed to load dialogue i hope you kill yourself\n");
		ds.isActive = 0; // prevent dereferencing
		return;
	}

	DialogueSystem_Init(&ds, lines, lineCount);
	dialogueJustStarted = 1;
}

void game_update(void) {

	// DO NOT USE TRIGGER
	// idk why but. yeah -jelly
	// PS. also do not shift this beyond the clearbackground else the cool fade disappears
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		isGamePaused = true;
	}

	if (isGamePaused)
	{
		PauseGame();
		CP_Image_Draw(vignette, 800, 450, 1600, 900, 10); // IT FADES 
		return; // pauses lol the whole deltatime thing was just a SCAMMMM
	}

	CP_Vector centerOfScreen = CP_Vector_Set(CP_System_GetWindowWidth() * .5f, CP_System_GetWindowHeight() * .5f);
	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));

	// draw the room first so it blocks everything else from updating
	// player is gone but will appear when dialogue is over. unintentional-ish
	// but it kinda makes it look like the player is leaving the lift ykykykyk -jelly
	Room_Update();

	// fucken hell this took me so long
	if (!ds.isActive) // || dialogueJustStarted
	{
		UpdateMonsterRedBaby();
		UpdateMonsterBaby();
		Player_Update(&player);
	}

	if (ds.isActive) {
		DialogueSystem_Update(&ds);
		DialogueSystem_Draw(&ds);

		if (dialogueJustStarted) {
			// allow one update tick before pausing
			dialogueJustStarted = 0; // next frame will be paused
		} 
		return; // skip further updates while dialogue is active lalallaa
	}

	if (DialogueSystem_IsFinished(&ds)) {
		CP_Font_DrawText("Dialogue finished!", 400, 360);
	}

	//Room_Update();

	////room rendering end.
	////printf("Player X Position: %.3f\n", player.currentPositionX);
	////UpdateMonsters
	//UpdateMonsterRedBaby();
	//UpdateMonsterBaby();

	//Player_Update(&player);

	DrawButtonUsingImage(settingsButtonBG, &settingsButton, pauseTextTemplate);

	// Calculate player movement delta (velocity) since last frame
	playerX = player.currentPositionX; playerY = player.currentPositionY;
	float dx = playerX - lastPlayerX;  // playerDX: horizontal movement from last frame
	float dy = playerY - lastPlayerY;  // playerDY: vertical movement from last frame
	lastPlayerX = playerX; lastPlayerY = playerY;

	UpdateCamera(&camera, player.currentPositionX, player.currentPositionY, dx, dy, 0.7f); //test case, please edit later. Read camera.c for more info. -day

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
	CP_Graphics_DrawRect(centerOfScreen.x - playerX, centerOfScreen.y - playerY, 50, 50);
	//End game if player kenna eaten (throw to a function if you wanna)
	if (player.currentHealth <= 0 && !player.toDraw)
	{
		//Draw you died

		if (FadeIn < 170)
		{
			FadeIn += (20.f * DeltaTime());
	
		}
		CP_Image_Draw(youDiedImage, 800, 450, 1600, 900, (int)FadeIn);
	


		if (CP_Input_KeyReleased(KEY_ANY))
		{
			StartTransition();
			nextScene = MAIN;
		}
		TransitionFadeIn(1.f, 0, 0, 0, 255);
		TransitionFadeOut(.5f, nextScene);
	}

	
	if (IsDebugging()) {
		ShowDebugInfo();
	}
	if (CP_Input_KeyReleased(KEY_P)) {
		ToggleDebug();
	}
}

void game_exit(void) {
	Player_Unload();
	Monsters_Unload();
	Interactable_Unload();

	//Level Unload
	CP_Image_Free(buttonBG);
	CP_Image_Free(vignette);
	CP_Image_Free(youDiedImage);
	for (int i = 0; i < 3; i++) {
		CP_Image_Free(Bg1_i[i]);
	}
	for (int i = 0; i < 3; i++) {
		CP_Image_Free(Bg2_i[i]);
	}
	for (int i = 0; i < 3; i++) {
		CP_Image_Free(Bg3_i[i]);
	}
	CP_Font_Free(pauseTextTemplate.font);
}

void PauseGame(void)
{
	isGamePaused = true; 

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 80));
	CP_Settings_TextSize(80);
	CP_Font_DrawText("PAUSED", 800, 250);

	DrawButtonUsingImage(buttonBG, &resumeButton, pauseTextTemplate);
	DrawButtonUsingImage(buttonBG, &quitButton, pauseTextTemplate);

	CP_Settings_TextSize(40);
	knobColor = CP_Color_Create(102, 102, 102, 255);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("Master Volume", 1020, 350);
	UpdateVolumeSlider(&masterSlider, AudioGetMasterVolume, AudioSetMasterVolume, -1, knobColor);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("BGM Volume", 1000, 450);
	UpdateVolumeSlider(&BGMSlider, AudioGetBGMVolume, AudioSetBGMVolume, 0, knobColor);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("SFX Volume", 1000, 550);
	UpdateVolumeSlider(&SFXSlider, AudioGetSFXVolume, AudioSetSFXVolume, 1, knobColor);

	TransitionFadeIn(1.f, 0, 0, 0, 0);
	TransitionFadeOut(.5f, sceneChange);
}

void ResumeGame(void) {
	isGamePaused = false;
}

void QuitGame(void) {
	StartTransition();
	isGamePaused = false;

	// they move after a while but lalallaa
	sceneChange = MAIN;
}

void InitialiseInteractables(void) {
	Interactable_InitialiseData();

	//array set a
	doorTest = Interactable_CreateDoor(-300.f, 20.f, &LockerTest);
	interactablesArray_a[0] = &doorTest;


	oilBlobTest = Interactable_CreateOilBlob(300.f, 0.f, &Interactable_OilInteraction);
	interactablesArray_a[1] = &oilBlobTest;

	liftTest = Interactable_CreateLift(0.f, 0.f, &LiftTest);
	interactablesArray_a[2] = &liftTest;

	//array set b
	doorTest = Interactable_CreateDoor(0.f, 20.f, &LockerTest);
	interactablesArray_b[0] = &doorTest;

	oilBlobTest = Interactable_CreateOilBlob(500.f, 0.f, &Interactable_OilInteraction);
	interactablesArray_b[1] = &oilBlobTest;

	//array set c
	doorTest = Interactable_CreateDoor(300.f, 20.f, &LockerTest);
	interactablesArray_c[0] = &doorTest;

	oilBlobTest = Interactable_CreateOilBlob(0.f, 0.f, &Interactable_OilInteraction);
	interactablesArray_c[1] = &oilBlobTest;
}

void LockerTest(void) {
	Interactable_DoorInteraction(&doorTest, &player);
}

void LiftTest(void) {
	Interactable_LiftInteraction(&liftTest, &player);
}

void InitialiseRooms(void) {
	Bg1_i[0] = CP_Image_Load("Assets/BG1Back.png");
	Bg2_i[0] = CP_Image_Load("Assets/BG2Back.png");
	Bg3_i[0] = CP_Image_Load("Assets/BG3Back.png");

	Bg1_i[1] = Bg2_i[1] = Bg3_i[1] = CP_Image_Load("Assets/Ground.png");

	Bg1_i[2] = Bg2_i[2] = Bg3_i[2] = CP_Image_Load("Assets/Ceiling.png");

	for (int i = 0; i < 3; i++)
	{
		Bg1_sd[i] = Bg2_sd[i] = Bg3_sd[i] = SpriteData_Create(1600, 900, 0, 0, 255.f);

		Bg1_ss[i] = Spritesheet_Create(Bg1_i[i], CP_Image_GetWidth(Bg1_i[i]), CP_Image_GetHeight(Bg1_i[i]));
		Bg2_ss[i] = Spritesheet_Create(Bg2_i[i], CP_Image_GetWidth(Bg2_i[i]), CP_Image_GetHeight(Bg2_i[i]));
		Bg3_ss[i] = Spritesheet_Create(Bg3_i[i], CP_Image_GetWidth(Bg3_i[i]), CP_Image_GetHeight(Bg3_i[i]));
	}

	Room presetMain = Room_Create(Bg2_ss, Bg2_sd, 3, interactablesArray_a, 3);
	Room presetDefaultA = Room_Create(Bg3_ss, Bg3_sd, 3, interactablesArray_b, 2);
	Room presetDefaultB = Room_Create(Bg1_ss, Bg1_sd, 3, interactablesArray_c, 2);

	Room roomPresets[] = { presetMain, presetDefaultA, presetDefaultB };

	for (int i = 0; i < roomCount; i++)
	{
		*roomList[i] = GenerateRoom(roomPresets, 2, i == centerRoomIndex);
	}
}

void Room_Update(void) {
	//clear console cause holy shit i get headache trying to read -day
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n Player Position: %0.3f\n", player.currentPositionX);
	//room render checking
	for (int i = 0; i < roomCount + 2; i++)
	{
		float pX = player.currentPositionX, pY = player.currentPositionY;

		int sightCheckP1 = (int)pX + RENDER_RANGE, sightCheckP2 = (int)pX - RENDER_RANGE;
		if (i < roomCount)
		{
			int sightCheckR = (i - centerRoomIndex) * 1600;
			//only load rooms in view (to save space!!!)
			if (sightCheckR <  sightCheckP1 && sightCheckR > sightCheckP2)
			{
				Room_Load(roomList[i], player, i - centerRoomIndex);
				//printf("Loading Room %d\n", i);
			}
		}
		//edge case left room loop to right.
		else if (i == roomCount)
		{
			int sightCheckR = (centerRoomIndex - roomCount) * 1600;

			if (sightCheckR <  sightCheckP1 && sightCheckR > sightCheckP2)
			{
				Room_Load(roomList[roomCount - 1], player, centerRoomIndex - roomCount);
				//printf("Loading Room: LOOP LEFT\n");
				if (pX < sightCheckR)
				{
					player.currentPositionX += roomCount * 1600;
					//TeleportMonsterRoom((roomCount * 1600));
					//printf("Looping Left to Right\n");
				}
			}
		}
		//edge case rignt room loop to left.
		else if (i > roomCount)
		{
			int sightCheckR = (roomCount - centerRoomIndex) * 1600;
			if (sightCheckR <  sightCheckP1 && sightCheckR > sightCheckP2)
			{
				Room_Load(roomList[0], player, roomCount - centerRoomIndex);
				//printf("Loading Room: LOOP RIGHT\n");
				if (pX > sightCheckR)
				{
					player.currentPositionX -= roomCount * 1600;
					//TeleportMonsterRoom(-1 * (roomCount * 1600));
					//printf("Looping Right to Left\n");
				}
			}
		}
	}
}