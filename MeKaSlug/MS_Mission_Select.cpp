#include "stdafx.h"
#include "MS_Mission_Select.h"
#include "Trans_Renderer.h"

MS_Mission_Select::MS_Mission_Select() : Speed(1500.0f), Activate(false)
{
}


MS_Mission_Select::~MS_Mission_Select()
{
}

void MS_Mission_Select::Init()
{
	Trans_Renderer* MSBG = Create_Renderer<Trans_Renderer>(6);
	MSBG->Set_Sprite(L"Mission_Select.bmp");
	MSBG->Set_TransColor(VIOLET);
	MSBG->size({ 450, 75 });

	m_Pos = { 400, -100 };
}

void MS_Mission_Select::Update()
{
	if (m_Pos.Y < 300)
	{
		m_Pos.Y += Speed * DELTATIME;
	}
	else
	{
		Activate = true;
	}
}