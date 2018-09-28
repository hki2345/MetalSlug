#include "stdafx.h"
#include "Effect_Bradley.h"

#include "Animator.h"


Effect_Bradley::Effect_Bradley()
{
}


Effect_Bradley::~Effect_Bradley()
{
}

void Effect_Bradley::Start(const Positionf& _Pos, const bool& _Raise)
{
	m_Pos = _Pos;
	float Ani_Time = .04f;
	p_Render = Create_Renderer<Animator>(30);

	if (true == _Raise)
	{
		p_Render->Set_Animation(L"Bradley_Bullet_Effect.bmp", L"Effect_Bullet", 0, 18, Ani_Time, false);
		p_Render->Change_Animation(L"Effect_Bullet", false);
	}
	else
	{
		p_Render->Set_Animation(L"Bradley_Bullet_Effect.bmp", L"Effect_Bullet", 20, 28, Ani_Time, false);
		p_Render->Change_Animation(L"Effect_Bullet", false);
	}

	
	p_Render->Set_TransColor(ORANGE);
}

void Effect_Bradley::Update()
{
	if (false == p_Render->IsActing())
	{
		Death(true);
	}
}