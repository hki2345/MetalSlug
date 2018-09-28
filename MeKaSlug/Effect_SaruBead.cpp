#include "stdafx.h"
#include "Effect_SaruBead.h"


#include "Animator.h"

Effect_SaruBead::Effect_SaruBead()
{
}


Effect_SaruBead::~Effect_SaruBead()
{
}

void Effect_SaruBead::Start(const Positionf& _Pos)
{
	m_Pos = _Pos;

	Speed = 300.0f;
	float Ani_Time = .04f;
	p_Render = Create_Renderer<Animator>(30);
	p_Render->Set_Animation(L"Sarubia_Bullet.bmp", L"Effect_Bullet", 35, 49, Ani_Time, true);
	p_Render->Change_Animation(L"Effect_Bullet", false);
	p_Render->Set_TransColor(ORANGE);
}

void Effect_SaruBead::Update()
{
	TheOne::Update_Gravity();
	if (Obj_Stand == m_Status_Obj)
	{
		Death(true);
	}

	m_Pos.X += Speed * DELTATIME;
}