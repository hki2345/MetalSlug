#include "stdafx.h"
#include "State_Stage02.h"

#include "One_Stage2.h"
#include "Item_Heavy.h"
#include "Player_Leona.h"
#include "Player_Eri.h"
#include "Pinset_Renderer.h"
#include "Sound_Player.h"
#include "ResourceManager.h"

#include "One_Data_Loader.h"

#include "One_Stage_SCover.h"
#include "One_Stage_CCover.h"

#include "PlayerMgr.h"

#include "Core.h"

State_Stage02::State_Stage02()
{
}


State_Stage02::~State_Stage02()
{
}


void State_Stage02::StateStart()
{
	BaseState::Init_UI({ 100, 300 }, L"Coal_Mine.mp3", L"MISSION_2.mp3");
}

void State_Stage02::StateUpdate()
{
	BaseState::Update_UI(L"Stage03");
}

void State_Stage02::All_SetUp()
{
	StateOfOne_Create<One_Stage2>();
	m_p_Load = StateOfOne_Create<One_Data_Loader>();

	BaseState::Init_Camera(L"Stage2");

	COLLIDERMANAGER.Link(Name(), L"Player", L"Enemy");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Item");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Weapon");

	COLLIDERMANAGER.Link(Name(), L"Enemy", L"Weapon");
	m_Wchar_Map = L"Stage2_Collider.bmp";
}

void State_Stage02::Value_DebugRender()
{
	// 특정 포맷의 문자열을 소스 문자열로 복사해준다.
	WCHAR Str[100] = { 0, };

	static float Frame = 0;
	Frame++;

	// DeltaTime : 1 = 1 : x; 
	swprintf_s(Str, L"FPS: %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 20, Str);

	swprintf_s(Str, L"Stage: Stage 2");
	TEXT_OUT(100, 40, Str);
}