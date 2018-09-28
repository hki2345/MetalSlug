#include "stdafx.h"
#include "State_Stage01.h"

#include "One_Stage1.h"

#include "Item_Heavy.h"
#include "Pinset_Renderer.h"
#include "Sound_Player.h"
#include "ResourceManager.h"

#include "One_Data_Loader.h"

#include "PlayerMgr.h"

#include "Core.h"

State_Stage01::State_Stage01()
{
}


State_Stage01::~State_Stage01()
{
}


void State_Stage01::StateStart()
{
	BaseState::Init_UI({0, 700}, L"Scrap_Island.mp3", L"MISSION_1.mp3");
}


void State_Stage01::StateUpdate()
{
	BaseState::Update_UI(L"Stage02");
}

void State_Stage01::All_SetUp()
{
	PATHMANAGER.CreateGamePath(L"Stage", L"Image\\Stage");
	PATHMANAGER.CreateGamePath(L"UI", L"Image\\UI");

	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Stage", L"Stage_Cover_Start.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Stage", L"Stage_Cover_Close.bmp").c_str());


	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"UI", L"Big_Orange.bmp").c_str(), { 10, 1 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"UI", L"Blue.bmp").c_str(), { 10, 1 });
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"UI", L"Orange.bmp").c_str(), {10, 1});
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"UI", L"Yellow.bmp").c_str(), {10, 1});
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"UI", L"Multi_Yellow.bmp").c_str(), {10, 4});
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"UI", L"Multi_Orange.bmp").c_str(), {10, 4});
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"UI", L"UI_Armo.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"UI", L"UI_Cannon.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"UI", L"UI_Status.bmp").c_str());

	StateOfOne_Create<One_Stage1>();
	m_p_Load = StateOfOne_Create<One_Data_Loader>();
	BaseState::Init_Camera(L"Stage1");



	COLLIDERMANAGER.Link(Name(), L"Player", L"Enemy");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Item");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Weapon");

	COLLIDERMANAGER.Link(Name(), L"Enemy", L"Weapon");
	m_Wchar_Map = L"Stage1_Collider.bmp";
	
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Scrap_Island.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Coal_Mine.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Combat_School.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Final_Attack.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "MISSION_1.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "MISSION_2.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "FINAL_MISSION_START.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Carry_Out.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Melody_of_My_Own_Way.mp3"));
}

void State_Stage01::Value_DebugRender()
{
	// 특정 포맷의 문자열을 소스 문자열로 복사해준다.
	WCHAR Str[100] = { 0, };

	static float Frame = 0;
	Frame++;

	swprintf_s(Str, L"Stage: Stage 1");
	TEXT_OUT(100, 20, Str);
	
	// DeltaTime : 1 = 1 : x; 
	swprintf_s(Str, L"FPS: %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 40, Str);

	swprintf_s(Str, L"Camera Pos: %d  %d", CameraIntPos().X, CameraIntPos().Y);
	TEXT_OUT(100, 60, Str);
}