#include "stdafx.h"
#include "State_Boss.h"

#include "One_BS_Cover.h"

#include "Pinset_FixData.h"
#include "Sound_Player.h"
#include "One_Stage_SCover.h"
#include "One_MultiFont.h"
#include "One_NumberFont.h"
#include "Trans_Renderer.h"
#include "ResourceManager.h"

#include "One_StageBoss.h"
#include "Player_Leona.h"
#include "Player_Eri.h"
#include "Enemy_Bomb.h"
#include "Item_Heavy.h"
#include "One_Data_Loader.h"
#include "Enemy_Boss.h"
#include "Boss_Bottom.h"

#include "PlayerMgr.h"
#include "BossMgr.h"

#include "Core.h"

State_Boss::State_Boss()
{
}


State_Boss::~State_Boss()
{
}

void State_Boss::StateStart()
{
	m_Time = .5f;
	m_State_Time = .0f;

	switch (PlayerMgr::character())
	{
	case PlayerMgr::Play_Character::Leona:
		m_p_Player = StateOfOne_Create<Player_Leona>();
		break;
	case PlayerMgr::Play_Character::Eri:
		m_p_Player = StateOfOne_Create<Player_Eri>();
		break;
		//  디버그 용도
	default:
		m_p_Player = StateOfOne_Create<Player_Leona>();
		break;
	}



	m_Multi_Life = StateOfOne_Create<One_MultiFont>();
	m_Multi_Life->Init_Setting(5, L"Multi_Yellow.bmp", Positionf{ 125.0f, 100.0f }, Positionf{ 100.0f, 20.0f });
	m_Multi_Life->Set_String(L"1UP=2");
	m_Multi_Life->Set_TransColor(RGB(255, 0, 255));

	m_Multi_Armo = StateOfOne_Create<One_MultiFont>();
	m_Multi_Armo->Init_Setting(3, L"Multi_Orange.bmp", Positionf{ 125.0f, 175.0f }, Positionf{ 60.0f, 20.0f }, 3);
	m_Multi_Armo->Set_String(L"<>?");
	m_Multi_Armo->Set_TransColor(RGB(255, 0, 255));

	m_NumMulti_Bomb = StateOfOne_Create<One_NumberFont>();
	m_NumMulti_Bomb->Init_Setting(2, L"Orange.bmp", Positionf{ 175.0f, 175.0f }, Positionf{ 40.0f, 20.0f });
	m_NumMulti_Bomb->Set_Number(99);
	m_NumMulti_Bomb->Set_TransColor(RGB(255, 0, 255));

	m_NumMulti_Score = StateOfOne_Create<One_NumberFont>();
	m_NumMulti_Score->Init_Setting(6, L"Blue.bmp", Positionf{ 125.0f, 50.0f }, Positionf{ 120.0f, 20.0f });
	m_NumMulti_Score->Set_Number(0);
	m_NumMulti_Score->Set_TransColor(RGB(255, 0, 255));

	m_Armo_Bomb = m_Multi_Armo->Create_Renderer<Trans_Renderer>(50);
	m_Armo_Bomb->Set_Sprite(L"UI_Armo.bmp");
	m_Armo_Bomb->Set_TransColor(RGB(255, 0, 255));

	PlayerMgr::MainPlayer(m_p_Player);
	m_p_Player->pos({ 100, 700 });
	m_p_Player->auto_Move(true);

	m_SCover = StateOfOne_Create<One_Stage_SCover>();
	m_SCover->Start(CameraPos());
	m_CCover = nullptr;


	RESOURCEMANAGER.Play_Sound(L"FINAL_MISSION_START.mp3");
}

void State_Boss::StateUpdate()
{ 

	if (KEYMANAGER.KEY_DOWN("Value_Debug") || KEYMANAGER.KEY_DOWN("Obj_Debug"))
	{
		CORE.Value_Debug_Switch();
		CORE.Obj_Debug_Switch();
	}

	if (nullptr == m_p_Player) { return; }


	// 보스가 죽은 최종시점
	if( nullptr != p_Boss && true == p_Boss->BossDie())		
	{
		m_Time += DELTATIME;
		if (m_Time > m_State_Time && false == m_GameOver)
		{
			One_BS_Cover* m_CCover = StateOfOne_Create<One_BS_Cover>();
			m_CCover->Init_FadeIn(true);

			p_Sound_Player->BGM_Play(L"Carry_Out.mp3");
			m_GameOver = true;
		}
		if (m_Time > m_State_Time * 2.0f)
		{
			CORE.ActingStateChanger(L"StageEnd");
		}

		return;
	}



	if (m_State_Time > m_Time)
	{
		m_p_Player->auto_Move(false);
	}
	else
	{
		m_State_Time += DELTATIME;
	}

	// 카메라가 플레이어를 따라다니는 시점
	if (true == m_State_Over)
	{
		BGM_LOOP;
		
		if (nullptr != p_Boss && true == p_Boss->BossRise())
		{
			if (700 < CameraPos().Y)
			{
				CameraPos({ CameraPos().X, 700});
			}
			else if (700 > CameraPos().Y)
			{
				CameraPos(Positionf{ CameraPos().X,  CameraPos().Y } + Positionf{0.0f, 100.0f * DELTATIME });
			}
		}
		else
		{
			if (523 < CameraPos().Y)
			{
				CameraPos(Positionf{ CameraPos().X,  CameraPos().Y } - Positionf{ 0.0f, 100.0f * DELTATIME });
			}
			else if (523 > CameraPos().Y)
			{
				CameraPos({ CameraPos().X, 523 });
			}
		}

		if (CameraPos().X + CORE.GetSize().PartX() < PlayerMgr::MainPlayer()->pos().X)
		{
			CameraPos(Positionf{ CameraPos().X,  CameraPos().Y } +
				Positionf{ MATHMANAGER.Absolute_Num(CameraPos().X + CORE.GetSize().PartX() - PlayerMgr::MainPlayer()->pos().X) * DELTATIME, 0 });
		}
		else if (CameraPos().X + CORE.GetSize().PartX() > PlayerMgr::MainPlayer()->pos().X)
		{
			CameraPos(Positionf{ CameraPos().X,  CameraPos().Y } -
				Positionf{ MATHMANAGER.Absolute_Num(CameraPos().X + CORE.GetSize().PartX() - PlayerMgr::MainPlayer()->pos().X)* DELTATIME, 0 });
		}

		// 카메라 고정
		if (CameraPos().X < 1600)
		{
			CameraPos(Positionf{ 1600,  CameraPos().Y });
		}
		else if (CameraPos().X > 2500)
		{
			CameraPos(Positionf{ 2500,  CameraPos().Y });
		}
	}
	else if (false == m_State_Over)
	{
		if (m_pos_Camera.X > m_CurPinset->m_Pos.X - m_Camera_space_size &&
			m_pos_Camera.X < m_CurPinset->m_Pos.X + m_Camera_space_size &&
			m_pos_Camera.Y > m_CurPinset->m_Pos.Y - m_Camera_space_size &&
			m_pos_Camera.Y < m_CurPinset->m_Pos.Y + m_Camera_space_size)
		{
			m_pos_Camera = m_CurPinset->m_Pos;
		}
		else
		{
			ToMoveCamera(m_CurPinset->m_Pos);
		}

		// 플레이어 방면 어디쪽이냐에 따라 나뉨
		// 플레이어가 핀셋보다 오른쪽에 잇을 경우
		if (m_CurPinset->m_pos_Dir == Vector2::Right)
		{
			if (PlayerMgr::MainPlayer()->pos().X > m_CurPinset->m_Pos.X + CORE.GetSize().PartX() + m_Camera_space_size &&
				PlayerMgr::SaruCnt() >= m_CurPinset->m_Num)
			{
				PlayerMgr::ResetEnemyCnt();
				Pinset_FixData* NewPin = SearchPinset();

				// 마지막 핀셋이라는 예기
				if (nullptr == NewPin)
				{
					m_Time = .0f;
					m_State_Time = 10.0f;

					m_State_Over = true;
					m_GameOver = false;
					p_Boss = StateOfOne_Create<Enemy_Boss>();
					BossMgr::MainBoss(p_Boss);

					p_Sound_Player = RESOURCEMANAGER.Rental_SoundPlayer();
					p_Sound_Player->BGM_Play(L"Final_Attack.mp3", .5f);
					return;
				}

				m_State_Over = false;
				m_CameraSpdX = (int)MATHMANAGER.Absolute_Num(m_CurPinset->m_Pos.X - NewPin->m_Pos.X);
				m_CameraSpdY = (int)MATHMANAGER.Absolute_Num(m_CurPinset->m_Pos.Y - NewPin->m_Pos.Y);

				m_CameraDir = MATHMANAGER.PntToPnt_Dir(NewPin->m_Pos, m_CurPinset->m_Pos);

				Pinset_FixData* PrevPin = m_CurPinset;
				m_CurPinset = NewPin;



				DataStartIter = m_ListData.begin();
				DataEndIter = m_ListData.end();

				for (; DataStartIter != DataEndIter; DataStartIter++)
				{
					if (PrevPin == (*DataStartIter))
					{
						NEW_DELETE(PrevPin);
						m_ListData.erase(DataStartIter);
						break;
					}
				}
			}
		}

		if (nullptr != m_SCover && false == m_SCover->Cover_Acting())
		{
			m_SCover->Death(true);
			m_SCover = nullptr;
		}
	}


	m_Multi_Life->pos(CameraIntPos() + Position{ 100.0f, 75.0f });
	m_Multi_Armo->pos(CameraIntPos() + Position{ 250.0f, 75.0f });
	m_NumMulti_Bomb->pos(CameraIntPos() + Position{ 320.0f, 75.0f });
	m_NumMulti_Score->pos(CameraIntPos() + Position{ 100.0f, 50.0f });
	m_Armo_Bomb->Pivot(Position{ 30.0f, -10.0f });
}

void State_Boss::All_SetUp()
{
	StateOfOne_Create<One_StageBoss>();
	StateOfOne_Create<Item_Heavy>();
	m_p_Load = StateOfOne_Create<One_Data_Loader>();

	BaseState::Init_Camera(L"Stage4");

	COLLIDERMANAGER.Link(Name(), L"Player", L"Enemy");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Item");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Weapon");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Bottom");

	COLLIDERMANAGER.Link(Name(), L"Enemy", L"Weapon");

	m_Wchar_Map = L"StageBoss_Collider.bmp";


	for (size_t i = 0; i < 8; i++)
	{
		Boss_Bottom* Bottom = StateOfOne_Create<Boss_Bottom>();
		Bottom->Start(i, 8);
	}
}

void State_Boss::Value_DebugRender()
{
	// 특정 포맷의 문자열을 소스 문자열로 복사해준다.
	WCHAR Str[100] = { 0, };

	static float Frame = 0;
	Frame++;

	// DeltaTime : 1 = 1 : x; 
	swprintf_s(Str, L"FPS: %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 20, Str);

	swprintf_s(Str, L"Stage: Stage 3");
	TEXT_OUT(100, 40, Str);
}