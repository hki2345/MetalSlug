#include "stdafx.h"
#include "State_Enemy_Edit.h"

#include "One_Edit_Enemy.h"
#include "Player_Leona.h"

#include "One_Stage1Collider.h"
#include "One_Stage2Collider.h"
#include "One_Stage3Collider.h"
#include "One_StageBossCollider.h"

#include "One_Stage1.h"
#include "One_Stage2.h"
#include "One_Stage3.h"
#include "One_StageBoss.h"

#include "ResourceManager.h"
#include "Core.h"

State_Enemy_Edit::State_Enemy_Edit() : 
	m_EditStage(nullptr), m_On_Collider(false), m_Editor(nullptr)
{
}


State_Enemy_Edit::~State_Enemy_Edit()
{
}



void State_Enemy_Edit::Init_Data()
{
	// 초기화
	m_On_Collider = false;
	if (nullptr != m_EditStage) { m_EditStage->Death(true); }
	if (nullptr != m_Editor) { m_Editor->DataClear(); }
}

void State_Enemy_Edit::StateUpdate()
{
	if (true == One_Edit_Enemy::m_b_InDialog) { return; }

	if (KEYMANAGER.KEY_DOWN("Debug"))
	{
		CORE.ActingStateChanger(L"Title");
	}
	if (KEYMANAGER.KEY_DOWN("Leona"))
	{
		CORE.ActingStateChanger(L"Leona");
	}
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
	


	if (KEYMANAGER.KEY_DOWN("Stage1_Edit"))
	{
		m_Wchar_Map = L"Stage1_Collider.bmp";
		Init_Data();
		UpdateStage1();
	}
	if (KEYMANAGER.KEY_DOWN("Stage2_Edit"))
	{
		m_Wchar_Map = L"Stage2_Collider.bmp";
		Init_Data();
		UpdateStage2();
	}
	if (KEYMANAGER.KEY_DOWN("Stage3_Edit"))
	{
		m_Wchar_Map = L"Stage3_Collider.bmp";
		Init_Data();
		UpdateStage3();
	}
	if (KEYMANAGER.KEY_DOWN("StageBoss_Edit"))
	{
		m_Wchar_Map = L"StageBoss_Collider.bmp";
		Init_Data();
		UpdateStageBoss();
	}


	if (KEYMANAGER.KEY_DOWN("Collider"))
	{
		if (false == m_On_Collider)
		{
			m_On_Collider = true;
			UpdateStageCollider();
		}
		else
		{
			m_On_Collider = false;

			switch (m_v_EditStage)
			{
			case 1:
				UpdateStage1();
				break;
			case 2:
				UpdateStage2();
				break;
			case 3:
				UpdateStage3();
				break;
			case 4:
				UpdateStageBoss();
				break;
			default:
				break;
			}
		}
	}
}	

void State_Enemy_Edit::UpdateStageCollider()
{
	if (nullptr != m_EditStage) { m_EditStage->Death(true); }
	switch (m_v_EditStage)
	{
	case 1:
		m_EditStage = StateOfOne_Create<One_Stage1Collider>();
		break;
	case 2:
		m_EditStage = StateOfOne_Create<One_Stage2Collider>();
		break;
	case 3:
		m_EditStage = StateOfOne_Create<One_Stage3Collider>();
		break;
	case 4:
		m_EditStage = StateOfOne_Create<One_StageBossCollider>();
		break;
	default:
		break;
	}
}

void State_Enemy_Edit::UpdateStage1()
{
	m_EditStage = StateOfOne_Create<One_Stage1>();
	m_v_EditStage = 1;
}
void State_Enemy_Edit::UpdateStage2()
{
	m_EditStage = StateOfOne_Create<One_Stage2>();
	m_v_EditStage = 2;
}
void State_Enemy_Edit::UpdateStage3()
{
	m_EditStage = StateOfOne_Create<One_Stage3>();
	m_v_EditStage = 3;
}
void State_Enemy_Edit::UpdateStageBoss()
{
	m_EditStage = StateOfOne_Create<One_StageBoss>();
	m_v_EditStage = 4;
}


void State_Enemy_Edit::All_SetUp()
{
	PATHMANAGER.CreateGamePath(L"Data", L"Image\\Data");
	RESOURCEMANAGER.Load_Res_MultiSprite(PATHMANAGER.CreateFilePath(L"Data", L"Tileset.bmp").c_str(), { 4,3 });
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Map", L"Pinset.bmp").c_str());

	KEYMANAGER.SetUp_Command(L"Pinset", 'P');
	KEYMANAGER.SetUp_Command(L"Enemy_Save", 'Z');
	KEYMANAGER.SetUp_Command(L"Enemy_Load", 'X');
	KEYMANAGER.SetUp_Command(L"Enemy_Left", 'A');
	KEYMANAGER.SetUp_Command(L"Enemy_Right", 'D');
	KEYMANAGER.SetUp_Command(L"Stage1_Edit", 'Q');
	KEYMANAGER.SetUp_Command(L"Stage2_Edit", 'W');
	KEYMANAGER.SetUp_Command(L"Stage3_Edit", 'E');
	KEYMANAGER.SetUp_Command(L"StageBoss_Edit", 'R');
	KEYMANAGER.SetUp_Command(L"MouseLB", 'U', VK_LBUTTON);
	KEYMANAGER.SetUp_Command(L"MouseRB", VK_RBUTTON);

	UpdateStage1();
	m_Wchar_Map = L"Stage1_Collider.bmp";
	m_Editor = StateOfOne_Create<One_Edit_Enemy>();


	// 충돌체를 위함 - 없어도 된다. -> 작업엔 지장 없음
	// StateOfOne_Create<Player_Leona>();
	// COLLIDERMANAGER.Link(Name(), L"Player", L"Enemy");
}







void State_Enemy_Edit::Value_DebugRender()
{
	// 특정 포맷의 문자열을 소스 문자열로 복사해준다.
	WCHAR Str[100] = { 0, };

	static float Frame = 0;
	Frame++;

	// DeltaTime : 1 = 1 : x; 
	swprintf_s(Str, L"FPS: %3.2f", 1 / TIMEMANAGER.DeltaTime());
	TEXT_OUT(100, 20, Str);


	swprintf_s(Str, L"Camera Pos: %3.2f %3.2f", CameraPos().X, CameraPos().Y);
	TEXT_OUT(100, 40, Str);
}