#include "stdafx.h"
#include "One_BottomEffect.h"


One_BottomEffect::One_BottomEffect()
{
}


One_BottomEffect::~One_BottomEffect()
{
}

void One_BottomEffect::Start(const Positionf& _Pos)
{
	m_Pos = _Pos;
	float Ani_Time = .1f;
	p_Render = Create_Renderer<Animator>(30);
	p_Render->Set_Animation(L"Boss_Bottom_Effect.bmp", L"Effect", 0, 7, Ani_Time, true);
	p_Render->Change_Animation(L"Effect", false);
	p_Render->Pivot({ 10, 0 });
	p_Render->Set_TransColor(ORANGE);
}