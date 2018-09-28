#include "stdafx.h"
#include "State_End.h"

#include "ResourceManager.h"
#include "Sound_Player.h"

#include "One_BS_Cover.h"
#include "One_EndBG.h"

State_End::State_End()
{
}


State_End::~State_End()
{
}

void State_End::StateStart()
{
	One_BS_Cover* m_CCover = StateOfOne_Create<One_BS_Cover>();
	m_CCover->Init_FadeOut();

	p_Sound_Player = RESOURCEMANAGER.Rental_SoundPlayer();
	p_Sound_Player->BGM_Play(L"Melody_of_My_Own_Way.mp3");
}

void State_End::StateUpdate()
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

void State_End::All_SetUp()
{
	RESOURCEMANAGER.Load_Res_Sprite(PATHMANAGER.CreateFilePath(L"Title", L"End.bmp").c_str());
	One_EndBG* m_CCover = StateOfOne_Create<One_EndBG>();
}

void State_End::Value_DebugRender()
{
}