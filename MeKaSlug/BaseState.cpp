#include "stdafx.h"
#include <map>

#include "BaseState.h"
#include "Sound_Player.h"
#include "One_Data_Loader.h"

#include "One_Player.h"

#include "PlayerMgr.h"

#include "BaseEnemy.h"
#include "Pinset_FixData.h"

#include "ResourceManager.h"
#include "Player_Leona.h"
#include "Player_Eri.h"

#include "One_Stage_SCover.h"
#include "One_Stage_CCover.h"
#include "Trans_Renderer.h"

#include "One_MultiFont.h"
#include "One_NumberFont.h"


BaseState::BaseState()
{
}

// 현재 활동 중인 모든 인스턴스들을 지워준다.
BaseState::~BaseState()
{
	m_Start_Iter = m_list_StateOfOne.begin();
	m_End_Iter = m_list_StateOfOne.end();

	for ( ; m_Start_Iter != m_End_Iter; m_Start_Iter++)
	{
		NEW_DELETE(*m_Start_Iter);
	}

	m_list_StateOfOne.clear();



	if (m_ListData.size() != 0)
	{
		DataStartIter = m_ListData.begin();
		DataEndIter = m_ListData.end();

		for (; DataStartIter != DataEndIter; DataStartIter++)
		{
			NEW_DELETE(*DataStartIter);
		}
	}
}

void BaseState::Init()
{
	if (false == m_Create)
	{
		// this == GameState*
		this->All_SetUp();
		m_Create = true;
	}
}

void BaseState::Update()
{
	m_Start_Iter = m_list_StateOfOne.begin();
	m_End_Iter = m_list_StateOfOne.end();
	for (; m_Start_Iter != m_End_Iter; m_Start_Iter++)
	{
		KAssert(nullptr == (*m_Start_Iter));

		// 맞긴한데 느려짐 -> 이부분 생각해봐야할듯 -> 물어보장
		//if (true == (*m_Start_Iter)->Active())
		{
			(*m_Start_Iter)->Update();
		}
	}
}

void BaseState::Collision()
{
	COLLIDERMANAGER.Collision();
}

void BaseState::Release()
{
	RENDERMANAGER.Release();
	COLLIDERMANAGER.Release();

	m_Start_Iter = m_list_StateOfOne.begin();
	m_End_Iter = m_list_StateOfOne.end();
	
	for (; m_Start_Iter != m_End_Iter; )
	{	
		// 살았으면 for문을 계속 진행시킨다.
		if (true == (*m_Start_Iter)->Live())
		{
			m_Start_Iter++;
			continue;
		}

		// 아니면 해당 객체를 지운다.
		NEW_DELETE((*m_Start_Iter));
		m_Start_Iter = m_list_StateOfOne.erase(m_Start_Iter);
	}
}

void BaseState::Obj_DebugRender()
{
	COLLIDERMANAGER.Obj_DebugRender();

	m_Start_Iter = m_list_StateOfOne.begin();
	m_End_Iter = m_list_StateOfOne.end();
	for (; m_Start_Iter != m_End_Iter; m_Start_Iter++)
	{
		KAssert(nullptr == (*m_Start_Iter));
		(*m_Start_Iter)->DebugUpdate();
	}
}

void BaseState::Insert_Renderer(Renderer* _Renderer)
{
	RENDERMANAGER.Insert_Renderer(_Renderer, Name());
}

void BaseState::Insert_Collider(const WCHAR* _GroupName, Collider* _Collider)
{
	COLLIDERMANAGER.Insert_Collider(Name(), _GroupName, _Collider);
}

void BaseState::StateStart() {

}



/***************** PinSet ***************/

void BaseState::ToMoveCamera(Positionf _Pos)
{
	if ((CameraPos().X < m_CurPinset->m_Pos.X - m_Camera_space_size ||
		CameraPos().X > m_CurPinset->m_Pos.X + m_Camera_space_size))
	{
		float Dir;
		if (m_CameraDir.X <= .0f) { Dir = -1.0f; }
		else { Dir = 1.0f; }
		m_pos_Camera.X += Dir * (float)m_CameraSpdX * DELTATIME;
	}

	if((CameraPos().Y < m_CurPinset->m_Pos.Y - m_Camera_space_size ||
		CameraPos().Y > m_CurPinset->m_Pos.Y + m_Camera_space_size))
	{
		float Dir;
		if (m_CameraDir.Y <= .0f) { Dir = -1.0f; }
		else { Dir = 1.0f; }
		m_pos_Camera.Y += Dir * (float)m_CameraSpdY * DELTATIME;
	}
}

void BaseState::Update_Camera()
{
	if (nullptr == m_p_Player) { return; }


	if (m_State_Time > m_Time)
	{
		m_p_Player->auto_Move(false);
	}
	else
	{
		m_State_Time += DELTATIME;
	}


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
			Change_CurPinset();
		}
	}
	else if (m_CurPinset->m_pos_Dir == Vector2::Up)
	{
		if (PlayerMgr::MainPlayer()->pos().Y < m_CurPinset->m_Pos.Y + CORE.GetSize().PartY() + m_Camera_space_size)
		{
			Change_CurPinset();
		}
	}
	else if (m_CurPinset->m_pos_Dir == Vector2::Left)
	{

	}
	else if (m_CurPinset->m_pos_Dir == Vector2::Down)
	{

	}
	else
	{

	}
}

void BaseState::Change_CurPinset()
{
	PlayerMgr::ResetEnemyCnt();
	Pinset_FixData* NewPin = SearchPinset();

	// 마지막 핀셋이라는 예기
	if (nullptr == NewPin) 
	{
		m_p_Player->auto_Move(true);
		m_State_Over = true;
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

Pinset_FixData* BaseState::SearchPinset()
{
	size_t dis = -1;
	Pinset_FixData* Pin = nullptr;

	DataStartIter = m_ListData.begin();
	DataEndIter = m_ListData.end();

	for (; DataStartIter != DataEndIter; DataStartIter++)
	{
		if (m_CurPinset == (*DataStartIter)) { continue; }

		size_t NewDis = (size_t)MATHMANAGER.Distance(m_CurPinset->m_Pos, (*DataStartIter)->m_Pos);

		// 거리가 더작다 -> 다음 핀셋으로 알맞다.
		if (dis > NewDis)
		{
			Pin = (*DataStartIter);
			dis = NewDis;
		}
	}

	return Pin;
}

void BaseState::Init_Camera(const WCHAR* _Path)
{
	std::vector<Pinset_Renderer::PinsetData> m_vec_Pinset = m_p_Load->DataLoad(_Path);

	for (size_t i = 0; i < m_vec_Pinset.size(); i++)
	{
		Pinset_FixData* NewData = new Pinset_FixData();
		NewData->m_Pos = m_vec_Pinset[i].m_EPos;
		NewData->m_pos_Dir = m_vec_Pinset[i].m_DPos;

		Position temp = m_vec_Pinset[i].m_Condition;
		NewData->m_Index = (BaseEnemy::Enemy_DataIndex)temp.X;
		NewData->m_Num = temp.Y;

		m_ListData.push_back(NewData);
	}

	DataStartIter = m_ListData.begin();
	m_CurPinset = (*DataStartIter);

	CameraPos(m_CurPinset->m_Pos);

	m_CameraSpdX = 0;
	m_CameraSpdY = 0;

	m_Camera_space_size = 5;
}


/***************** UI ***************/

void BaseState::Init_UI(const Positionf& _StartPos, const WCHAR* _BGM, const WCHAR* _SND)
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
	m_Armo_Bomb->Set_TransColor(RGB(255,0,255));
	
	PlayerMgr::MainPlayer(m_p_Player);
	m_p_Player->pos(_StartPos);
	m_p_Player->auto_Move(true);

	m_SCover = StateOfOne_Create<One_Stage_SCover>();
	m_SCover->Start(CameraPos());
	m_CCover = nullptr;

	p_Sound_Player = RESOURCEMANAGER.Rental_SoundPlayer();
	p_Sound_Player->BGM_Play(_BGM, .5f);
	RESOURCEMANAGER.Play_Sound(_SND);
}

void BaseState::Update_UI(const WCHAR* _NextStage)
{
	BGM_LOOP;

	if (KEYMANAGER.KEY_DOWN("Value_Debug") || KEYMANAGER.KEY_DOWN("Obj_Debug"))
	{
		CORE.Value_Debug_Switch();
		CORE.Obj_Debug_Switch();
	}

	BaseState::Update_Camera();

	//if (KEYMANAGER.KEY_DOWN("Debug"))
	//{
	//	CORE.ActingStateChanger(L"Game");
	//}


	if (nullptr != m_SCover && false == m_SCover->Cover_Acting())
	{
		m_SCover->Death(true);
		m_SCover = nullptr;
	}

	// 게임 종료 시점
	if (nullptr != m_CCover && false == m_CCover->Cover_Acting())
	{
		p_Sound_Player->BGM_Stop();
		CORE.ActingStateChanger(_NextStage);
	}

	if (true == m_State_Over && nullptr == m_CCover)
	{
		m_CCover = StateOfOne_Create<One_Stage_CCover>();
		m_CCover->Start(CameraPos());
	}

	m_Multi_Life->pos(CameraIntPos() + Position{ 100.0f, 75.0f });
	m_Multi_Armo->pos(CameraIntPos() + Position{250.0f, 75.0f});
	m_NumMulti_Bomb->pos(CameraIntPos() + Position{ 320.0f, 75.0f });
	m_NumMulti_Score->pos(CameraIntPos() + Position{ 100.0f, 50.0f });
	m_Armo_Bomb->Pivot(Position{ 30.0f, -10.0f });
}
