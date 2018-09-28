#include "stdafx.h"
#include "Effect_FireWater.h"
#include "Animator.h"


Effect_FireWater::Effect_FireWater()
{
}


Effect_FireWater::~Effect_FireWater()
{
}

void Effect_FireWater::Start(const Positionf& _Pos)
{
	float Ani_Time = .04f;
	m_Pos = _Pos;
	p_Render = Create_Renderer<Animator>(8);
	p_Render->Set_Animation(L"Water_Effect.bmp", L"Effect", 0, 24, Ani_Time, false);
	p_Render->Change_Animation(L"Effect", false);
	p_Render->Pivot({ 0, 20 });
	p_Render->Set_TransColor(ORANGE);
}


void Effect_FireWater::Update()
{
	if (false == p_Render->IsActing())
	{
		Death(true);
	}
}