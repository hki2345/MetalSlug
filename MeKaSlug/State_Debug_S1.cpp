#include "stdafx.h"
#include "State_Debug_S1.h"

#include "One_Stage1.h"
#include "Player_Leona.h"
#include "Enemy_Bomb.h"
#include "Item_Heavy.h"
#include "One_Data_Loader.h"
#include "ResourceManager.h"

#include "PlayerMgr.h"

#include "Core.h"



State_Debug_S1::State_Debug_S1()
{
}


State_Debug_S1::~State_Debug_S1()
{
}

void State_Debug_S1::StateStart()
{
	BaseState::Init_UI({ 0, 700 }, L"Scrap_Island.mp3", L"MISSION_1.mp3");
}

void State_Debug_S1::StateUpdate()
{
	BaseState::Update_UI(L"Stage02");

	if (KEYMANAGER.KEY_DOWN("Debug"))
	{
		CORE.ActingStateChanger(L"Game");
	}
}

void State_Debug_S1::All_SetUp()
{
	StateOfOne_Create<One_Stage1>();
	m_p_Load = StateOfOne_Create<One_Data_Loader>();
	BaseState::Init_Camera(L"Stage1");

	COLLIDERMANAGER.Link(Name(), L"Player", L"Item");
	m_Wchar_Map = L"Stage1_Collider.bmp";
}

void State_Debug_S1::Value_DebugRender()
{
	// 특정 포맷의 문자열을 소스 문자열로 복사해준다.
	WCHAR Str[100] = { 0, };

	static float Frame = 0;
	Frame++;

	// DeltaTime : 1 = 1 : x; 
	swprintf_s(Str, L"FPS: %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 20, Str);

	swprintf_s(Str, L"Stage: Stage 1 Debug");
	TEXT_OUT(100, 40, Str);
}