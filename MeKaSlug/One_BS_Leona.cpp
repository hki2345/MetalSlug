#include "stdafx.h"
#include "One_BS_Leona.h"
#include "Animator.h"


One_BS_Leona::One_BS_Leona()
{
}


One_BS_Leona::~One_BS_Leona()
{
}

void One_BS_Leona::Start(TheOne* _Target)
{
	m_Target = _Target;
	float Ani_Time = .08f;
	float Jump_Ani_Time = .01f;

	Animator* p_RenderBody;
	Animator* p_RenderLeg;

	// 생성자 값은 레이어층
	p_RenderBody = Create_Renderer<Animator>(8);

	p_RenderBody->Set_Animation(L"Leona_NoGun_Body_Right.bmp", L"Right_Leona_NoGun_Body_Idle", 0, 3, Ani_Time, true);
	p_RenderBody->Change_Animation(L"Right_Leona_NoGun_Body_Idle");
	p_RenderBody->Pivot({ 0,-5});
	p_RenderBody->size({ 100, 100 });

	p_RenderLeg = Create_Renderer<Animator>(7);
	p_RenderLeg->Set_Animation(L"Leona_Leg_Right.bmp", L"Right_Leona_Leg_Idle", 0, 0, Ani_Time, true);
	p_RenderLeg->Change_Animation(L"Right_Leona_Leg_Idle");
	p_RenderLeg->Pivot({ 5, -5 });
	p_RenderLeg->size({ 100, 100 });

	p_RenderBody->Set_TransColor(RGB(255, 105, 0));
	p_RenderLeg->Set_TransColor(RGB(255, 105, 0));
}

void One_BS_Leona::Update()
{
	m_Pos = { m_Target->pos().X, m_Target->pos().Y + 75 };
}