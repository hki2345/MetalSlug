#include "stdafx.h"

#include "State_Title.h"
#include "One_Background.h"

#include "TimeManager.h"
#include "KeyManager.h"
#include "PathManager.h"
#include "ResourceManager.h"

#include "Sound_Player.h"

#include "Core.h"

State_Title::State_Title()
{
}


State_Title::~State_Title()
{
}

void State_Title::StateUpdate()
{
	if (KEYMANAGER.KEY_DOWN("Value_Debug") || KEYMANAGER.KEY_DOWN("Obj_Debug"))
	{
		CORE.Value_Debug_Switch();
		CORE.Obj_Debug_Switch();
	}

	if (KEYMANAGER.KEY_DOWN("Debug"))
	{
		p_Sound_Player->BGM_Stop();
		CORE.ActingStateChanger(L"Game");
	}
	if (KEYMANAGER.KEY_DOWN("Start"))
	{
		p_Sound_Player->BGM_Stop();
		CORE.ActingStateChanger(L"Military_System");
	}
}

void State_Title::Setting_Key()
{
	KEYMANAGER.SetUp_Command(L"Debug", 'G');
	KEYMANAGER.SetUp_Command(L"Start", VK_RETURN);
}

void State_Title::Setting_Image()
{
	PATHMANAGER.CreateGamePath(L"Sound");
	PATHMANAGER.CreateGamePath(L"Title", L"Image\\Title");
	PATHMANAGER.CreateGamePath(L"Player_Image", L"Image\\Player_Image");
	PATHMANAGER.CreateGamePath(L"MapData");
	
	//RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Title", L"1.bmp").c_str());
	WCHAR Num_Char[10];

	for (size_t i = 0; i < 64; i++)
	{
		_itow_s(i, Num_Char, 10);
		std::wstring Num_str = Num_Char;

		Num_str += L".bmp";
		RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Title", Num_str.c_str()).c_str());
	}

	StateOfOne_Create<One_BackGround>();
}

void State_Title::StateStart()
{
	p_Sound_Player = RESOURCEMANAGER.Rental_SoundPlayer();
	p_Sound_Player->BGM_Play(L"Title_Edit.mp3");
}

void State_Title::All_SetUp()
{
	// m.m.m.m.m.m.m.m
	Setting_Key();
	Setting_Image();

	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Title_Edit.mp3"));
}

void State_Title::Value_DebugRender()
{
	// 특정 포맷의 문자열을 소스 문자열로 복사해준다.
	WCHAR Str[100] = { 0, };

	// 초당 프레임 -> 1프레임을 몇 초만에 나타내는가
	// DeltaTime : 1 = 1 : x; 
	// 비례식 -> 델타타임 때 1프레임은 1초에 몇 프레임인가?
	swprintf_s(Str, L"FPS %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 60, Str);
}