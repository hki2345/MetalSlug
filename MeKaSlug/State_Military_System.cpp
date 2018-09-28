#include "stdafx.h"
#include "State_Military_System.h"

#include "TimeManager.h"
#include "KeyManager.h"
#include "PathManager.h"
#include "ResourceManager.h"

#include "Sound_Player.h"

#include "Core.h"

#include "One_MS_BackGround.h"
#include "One_BS_BackGround.h"
#include "One_BS_Cover.h"

#include "MS_Mission_Select.h"
#include "MS_Select_Normal.h"
#include "MS_Arrow_Side.h"



State_Military_System::State_Military_System() : 
	Arrow(nullptr), Select_Normal(nullptr), Select_Mission(nullptr), 
	MS_Back(nullptr), BS_Cover(nullptr), State_Count(0)
{
}


State_Military_System::~State_Military_System()
{
}


void State_Military_System::StateUpdate()
{
	BGM_LOOP;

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

	// 난이도 설정
	if (KEYMANAGER.KEY_DOWN("Start") && 0 == State_Count)
	{
		Select_Normal->Death(true);

		if (nullptr != Arrow)
		{
			Arrow->Death(true);
			Arrow = nullptr;
		}
		Select_Normal = nullptr;


		RESOURCEMANAGER.Play_Sound(L"Start_Effect.mp3", .5f);

		if (nullptr == Select_Mission)
		{
			Select_Mission = StateOfOne_Create<MS_Mission_Select>();
		}

		State_Count++;
	}

	// 미션 설정 -  진짜처럼 보이게 하기 위함
	else if (KEYMANAGER.KEY_DOWN("Start") && 1 == State_Count)
	{
		CORE.ActingStateChanger(L"Barracks");
	}

	// 화살표 최신화
	if (nullptr != Select_Normal && true == Select_Normal->activate() && Arrow == nullptr)
	{
		Arrow = StateOfOne_Create<MS_Arrow_Side>();
		Arrow->SetTarget(Select_Normal);
	}

	if (nullptr != Select_Mission && true == Select_Mission->activate() && Arrow == nullptr)
	{
		Arrow = StateOfOne_Create<MS_Arrow_Side>();
		Arrow->SetTarget(Select_Mission);
	}
}


void State_Military_System::Setting_Image()
{
	PATHMANAGER.CreateGamePath(L"The_Military_System", L"Image\\Military_System");

	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"The_Military_System", L"Military_System_BackGround.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"The_Military_System", L"Mission_Select.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"The_Military_System", L"Select_Normal.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"The_Military_System", L"Arrow_Right_Side.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"The_Military_System", L"Arrow_Left_Side.bmp").c_str());
}

void State_Military_System::StateStart()
{
	State_Count = 0;

	if (nullptr != Arrow)
	{
		Arrow->Death(true);
		Arrow = nullptr;
	}
	if (nullptr != Select_Mission)
	{
		Select_Mission->Death(true);
		Select_Mission = nullptr;
	}

	MS_Back = StateOfOne_Create<One_MS_BackGround>();
	Select_Normal = StateOfOne_Create<MS_Select_Normal>();

	p_Sound_Player = RESOURCEMANAGER.Rental_SoundPlayer();
	p_Sound_Player->BGM_Play(L"The_Military_System.mp3", .5f);
	RESOURCEMANAGER.Play_Sound(L"MS_Select.mp3");
}

void State_Military_System::All_SetUp()
{
	Setting_Image();

	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "The_Military_System.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "MS_Select.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Start_Effect.mp3"));
}

void State_Military_System::Value_DebugRender()
{
	WCHAR Str[100] = { 0, };
	swprintf_s(Str, L"FPS %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 60, Str);
}