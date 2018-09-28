#include "stdafx.h"
#include "Effect_MagmaCannon.h"

#include "Animator.h"

Effect_MagmaCannon::Effect_MagmaCannon()
{
}


Effect_MagmaCannon::~Effect_MagmaCannon()
{
}


void Effect_MagmaCannon::Start(TheOne* _Pos)
{
	float Ani_Time = .04f;
	p_Target = _Pos;
	p_Render = Create_Renderer<Animator>(30);
	p_Render->Set_Animation(L"MagmaEffect.bmp", L"Effect", 0, 11, Ani_Time, false);
	p_Render->Change_Animation(L"Effect", false);
	p_Render->Pivot({ 0, 0 });
	p_Render->Set_TransColor(ORANGE);
}

void Effect_MagmaCannon::Update()
{


	m_Pos = { p_Target->pos().X, p_Target->pos().Y + 250 };
	if (false == p_Render->IsActing())
	{
		Death(true);
	}
}