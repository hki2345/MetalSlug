#include "stdafx.h"
#include "One_BS_Select_Cover.h"
#include "Bit_Renderer.h"
#include "PlayerMgr.h"


One_BS_Select_Cover::One_BS_Select_Cover() : m_Speed(1500)
{
}


One_BS_Select_Cover::~One_BS_Select_Cover()
{
}


void One_BS_Select_Cover::Start(TheOne* _Target)
{
	m_Target = _Target;
	m_TargetPos = _Target->pos();

	Bit_Renderer* MSBG = Create_Renderer<Bit_Renderer>(6);
	MSBG->Set_Sprite(L"Select_Cover.bmp");
	m_Pos = { m_TargetPos.X, -400 };
}

void One_BS_Select_Cover::Update()
{
	if (m_Pos.Y < m_TargetPos.Y)
	{
		m_Pos.Y += m_Speed * DELTATIME;
	}
}