#include "stdafx.h"
#include "Effect_Tank.h"

#include "Animator.h"

Effect_Tank::Effect_Tank()
{
}


Effect_Tank::~Effect_Tank()
{
}

void Effect_Tank::Start(const Positionf& _Pos)
{
	m_Pos = _Pos;
	float Ani_Time = .04f;
	p_Render = Create_Renderer<Animator>(30);
	p_Render->Set_Animation(L"Tank_Effect.bmp", L"Effect_Bullet", 0, 13, Ani_Time, false);
	p_Render->Change_Animation(L"Effect_Bullet", false);
	p_Render->Set_TransColor(ORANGE);
}

void Effect_Tank::Update()
{
	if (false == p_Render->IsActing())
	{
		Death(true);
	}
}