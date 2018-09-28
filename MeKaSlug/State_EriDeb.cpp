#include "stdafx.h"
#include "State_EriDeb.h"

#include "ResourceManager.h"
#include "PlayerMgr.h"

#include "Player_Eri.h"
#include "Enemy_Walker.h"
#include "Item_Heavy.h"
#include "One_Stage1.h"

#include "Core.h"

State_EriDeb::State_EriDeb()
{
}


State_EriDeb::~State_EriDeb()
{
}

void State_EriDeb::StateStart()
{
	PlayerMgr::MainPlayer(m_p_Player);
	PlayerMgr::character(PlayerMgr::Play_Character::Eri);
}


void State_EriDeb::StateUpdate()
{
	if (KEYMANAGER.KEY_DOWN("Value_Debug"))
	{
		CORE.Value_Debug_Switch();
	}
	if (KEYMANAGER.KEY_DOWN("Obj_Debug"))
	{
		CORE.Obj_Debug_Switch();
	}

	if (KEYMANAGER.KEY_PRESS("CamerUp"))
	{
		MoveCamera(Vector2f::Up * CAMERA_SPD * DELTATIME);
	}
	if (KEYMANAGER.KEY_PRESS("CamerDown"))
	{
		MoveCamera(Vector2f::Down * CAMERA_SPD * DELTATIME);
	}
	if (KEYMANAGER.KEY_PRESS("CamerLeft"))
	{
		MoveCamera(Vector2f::Left * CAMERA_SPD * DELTATIME);
	}
	if (KEYMANAGER.KEY_PRESS("CamerRight"))
	{
		MoveCamera(Vector2f::Right * CAMERA_SPD * DELTATIME);
	}

	if (KEYMANAGER.KEY_DOWN("Debug"))
	{
		CORE.ActingStateChanger(L"Game");
	}
}


void State_EriDeb::Setting_Image()
{
	StateOfOne_Create<One_Stage1>();
	m_p_Player = StateOfOne_Create<Player_Eri>();
	StateOfOne_Create<Enemy_Walker>();
	StateOfOne_Create<Item_Heavy>();

	m_Wchar_Map = L"Stage1_Collider.bmp";
}

void State_EriDeb::Setting_Collider()
{
	COLLIDERMANAGER.Link(Name(), L"Player", L"Enemy");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Item");
	COLLIDERMANAGER.Link(Name(), L"Player", L"Weapon");

	COLLIDERMANAGER.Link(Name(), L"Enemy", L"Weapon");
}

void State_EriDeb::All_SetUp()
{
	CameraPos({ 0, 200 });
	Setting_Image();
	Setting_Collider();
}






void State_EriDeb::Value_DebugRender()
{
	// 특정 포맷의 문자열을 소스 문자열로 복사해준다.
	WCHAR Str[100] = { 0, };

	static float Frame = 0;
	Frame++;

	// DeltaTime : 1 = 1 : x; 
	swprintf_s(Str, L"FPS: %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 20, Str);

	swprintf_s(Str, L"Mouse Pos: %d, %d", CORE.GetMousePos().X, CORE.GetMousePos().Y);
	TEXT_OUT(100, 40, Str);

	swprintf_s(Str, L"Player Pos: %f, %f", m_p_Player->pos().X, m_p_Player->pos().Y);
	TEXT_OUT(100, 60, Str);

	swprintf_s(Str, L"Player To Mouse Dis: %f", MathManager::Inst().Distance(CORE.GetMousePos(), m_p_Player->pos()));
	TEXT_OUT(100, 80, Str);

	swprintf_s(Str, L"Player To Mouse Radian: %f", MathManager::Inst().Degree(CORE.GetMousePos(), m_p_Player->pos()));
	TEXT_OUT(100, 100, Str);

	Positionf DirPos = MathManager::Inst().PntToPnt_Dir(CORE.GetMousePos(), m_p_Player->pos());

	swprintf_s(Str, L"Player To Mouse Dir: %f %f", DirPos.X, DirPos.Y);
	TEXT_OUT(100, 120, Str);

}