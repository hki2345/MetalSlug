#include "stdafx.h"
#include "State_Barracks.h"

#include "Sound_Player.h"

#include "ResourceManager.h"
#include "Core.h"

#include "One_BS_BackGround.h"
#include "One_BS_Cover.h"
#include "One_BS_Front.h"
#include "One_BS_Select_Cover.h"
#include "One_BS_Select_Eri.h"
#include "One_BS_Select_Leona.h"
#include "One_BS_Pinset.h"
#include "One_BS_Eri.h"
#include "One_BS_Leona.h"

#include "PlayerMgr.h"

State_Barracks::State_Barracks() :
	BS_Back(nullptr),BS_Cover(nullptr), BS_Front(nullptr), BS_Select_Cover(nullptr),
	BS_Select_Eri (nullptr), BS_Select_Leona (nullptr), BS_Pinset(nullptr)
{
}


State_Barracks::~State_Barracks()
{
}


void State_Barracks::StateUpdate()
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


	// 커버 등장 시 게임 시작
	if(nullptr != BS_Select_Cover && false == BS_Cover->fade())
	{
		BS_Cover->Init_FadeIn();
		return;
	}

	// 진짜 게임 시작
	if (nullptr != BS_Select_Cover && true == BS_Cover->fade_check())
	{
		CORE.ActingStateChanger(L"Stage01");
	}

	// 커버 등장 시 조작 불가
	if (nullptr != BS_Select_Cover)
	{
		return;
	}

	// 캐릭터 선택
	switch (m_Player_Select)
	{
	case PlayerMgr::Play_Character::None_Char:
		Update_Init();
		break;
	case PlayerMgr::Play_Character::Eri:
		Update_Select_Eri();
		break;
	case PlayerMgr::Play_Character::Leona:
		Update_Select_Leona();
		break;
	default:
		break;
	}
	
	// 게임 시작
	if (KEYMANAGER.KEY_DOWN("Start"))
	{
		// 커버 작동중에는 사용 불가
		if (nullptr != BS_Cover && false == BS_Cover->fade_check())
		{
			return;
		}

		if (nullptr == BS_Select_Cover)
		{
			BS_Select_Cover = StateOfOne_Create<One_BS_Select_Cover>();

			switch (m_Player_Select)
			{
			case PlayerMgr::Play_Character::None_Char:
				break;
			case PlayerMgr::Play_Character::Eri:
			{
				RESOURCEMANAGER.Play_Sound(L"ERI.mp3", .5f);
				PlayerMgr::character(PlayerMgr::Play_Character::Eri);
				BS_Select_Cover->Start(BS_Select_Eri);

				One_BS_Eri* BS_Eri = StateOfOne_Create<One_BS_Eri>();
				BS_Eri->Start(BS_Select_Cover);				
			}
				break;

			case PlayerMgr::Play_Character::Leona:
			{
				RESOURCEMANAGER.Play_Sound(L"LEONA.mp3", .5f);
				PlayerMgr::character(PlayerMgr::Play_Character::Leona);
				BS_Select_Cover->Start(BS_Select_Leona);

				One_BS_Leona* BS_Leona = StateOfOne_Create<One_BS_Leona>();
				BS_Leona->Start(BS_Select_Cover);
				break;
			}
			default:
				break;
			}
		}
	}
}

void State_Barracks::Update_Init()
{
	if (nullptr != BS_Cover && true == BS_Cover->fade_check())
	{
		//BS_Pinset = StateOfOne_Create <One_BS_Pinset>();
		m_Player_Select = PlayerMgr::Play_Character::Eri;
	}
}
void State_Barracks::Update_Select_Eri()
{
	if (nullptr == BS_Select_Eri)
	{
		BS_Select_Eri = StateOfOne_Create<One_BS_Select_Eri>();
		//BS_Pinset->Update(BS_Select_Eri->pos().X);
	}

	// 캐릭터 설정
	if (KEYMANAGER.KEY_DOWN("Move_Left") || KEYMANAGER.KEY_DOWN("Move_Right"))
	{
		RESOURCEMANAGER.Play_Sound(L"BS_Select.mp3", .5f);
		BS_Select_Eri->Death(true);
		BS_Select_Eri = nullptr;
		m_Player_Select = PlayerMgr::Play_Character::Leona;
	}
}
void State_Barracks::Update_Select_Leona()
{
	if (nullptr == BS_Select_Leona)
	{
		BS_Select_Leona = StateOfOne_Create<One_BS_Select_Leona>();
		//BS_Pinset->Update(BS_Select_Leona->pos().X);
	}

	// 캐릭터 설정
	if (KEYMANAGER.KEY_DOWN("Move_Left") || KEYMANAGER.KEY_DOWN("Move_Right"))
	{
		RESOURCEMANAGER.Play_Sound(L"BS_Select.mp3", .5f);
		BS_Select_Leona->Death(true);
		BS_Select_Leona = nullptr;
		m_Player_Select = PlayerMgr::Play_Character::Eri;
	}
}

void State_Barracks::Setting_Image()
{
	PATHMANAGER.CreateGamePath(L"Barracks", L"Image\\Barracks");

	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Barracks", L"Barracks_BackGround.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Barracks", L"Barracks_Cover.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Barracks", L"Barracks_Front.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Barracks", L"Select_Character_Eri.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Barracks", L"Select_Character_Leona.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Barracks", L"Select_Cover.bmp").c_str());
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Barracks", L"BS_Pinset.bmp").c_str());
}

void State_Barracks::StateStart()
{
	p_Sound_Player = RESOURCEMANAGER.Rental_SoundPlayer();
	p_Sound_Player->BGM_Play(L"Barracks.mp3", .5f);
	RESOURCEMANAGER.Play_Sound(L"MS_Select.mp3");
}

void State_Barracks::All_SetUp()
{
	Setting_Image();
	BS_Back = StateOfOne_Create<One_BS_BackGround>();
	BS_Cover = StateOfOne_Create<One_BS_Cover>();
	StateOfOne_Create<One_BS_Front>();

	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "Barracks.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "BS_Select.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "ERI.mp3"));
	RESOURCEMANAGER.Load_Sound(FILE_PATH("Sound", "LEONA.mp3"));

	m_Player_Select = PlayerMgr::Play_Character::None_Char;
	BS_Cover->Init_FadeOut();
}			

void State_Barracks::Value_DebugRender()
{
	WCHAR Str[100] = { 0, };
	swprintf_s(Str, L"FPS %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 60, Str);
}