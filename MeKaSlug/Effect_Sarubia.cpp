#include "stdafx.h"
#include "Effect_Sarubia.h"

#include "Animator.h"

Effect_Sarubia::Effect_Sarubia()
{
}


Effect_Sarubia::~Effect_Sarubia()
{
}

void Effect_Sarubia::Start(const Positionf& _Pos)
{
	m_Pos = _Pos;
	float Ani_Time = .04f;
	p_Render = Create_Renderer<Animator>(30);
	p_Render->Set_Animation(L"Sarubia_Fire_Effect.bmp", L"Effect_Bullet", 0, 15, Ani_Time, false);
	p_Render->Change_Animation(L"Effect_Bullet", false);
	p_Render->Set_TransColor(ORANGE);
}

void Effect_Sarubia::Update()
{
	if (false == p_Render->IsActing())
	{
		Death(true);
	}
}