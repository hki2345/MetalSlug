#include "stdafx.h"
#include "MS_Select_Normal.h"
#include "Trans_Renderer.h"


MS_Select_Normal::MS_Select_Normal() : Speed(1500.0f), Activate(false)
{
}


MS_Select_Normal::~MS_Select_Normal()
{
}

void MS_Select_Normal::Init()
{
	Trans_Renderer* MSBG = Create_Renderer<Trans_Renderer>(6);
	MSBG->Set_Sprite(L"Select_Normal.bmp");
	MSBG->Set_TransColor(VIOLET);
	MSBG->size({ 600, 100 });

	m_Pos = { 400, -100 };
}

void MS_Select_Normal::Update()
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