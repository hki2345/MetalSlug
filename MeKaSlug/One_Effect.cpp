#include "stdafx.h"
#include "One_Effect.h"
#include "Animator.h"


One_Effect::One_Effect() : p_Render(nullptr)
{
}


One_Effect::~One_Effect()
{
}

void One_Effect::DebugUpdate()
{
	WCHAR Str[100] = { 0, };
	swprintf_s(Str, L"Effect Frame: %d", p_Render->CurAniFrame());
	TEXT_OUT((int)(m_Pos.X + 50), (int)(m_Pos.Y - 50), Str);
}

void One_Effect::Start(const Effect_Type& _Value, const Positionf& _Pos)
{
	this_Type = _Value;
	float Ani_Time = .04f;
	p_Render = Create_Renderer<Animator>(30);
	
	switch (this_Type)
	{
	case One_Effect::SMALL:
		p_Render->Set_Animation(L"Effect_Small.bmp", L"Effect_Small", 0, 27, Ani_Time, false);
		p_Render->Change_Animation(L"Effect_Small", false);
		break;
	case One_Effect::MIDDLE:
		p_Render->Set_Animation(L"Effect_Medium.bmp", L"Effect_Medium", 0, 27, Ani_Time, false);
		p_Render->Change_Animation(L"Effect_Medium", false);
		break;
	case One_Effect::BIG:
		p_Render->Set_Animation(L"Effect_Big.bmp", L"Effect_Big", 0, 27, Ani_Time, false);
		p_Render->Change_Animation(L"Effect_Big", false);
		break;
	case One_Effect::HUGE:
		p_Render->Set_Animation(L"Effect_Huge.bmp", L"Effect_Huge", 0, 23, Ani_Time, false);
		p_Render->Change_Animation(L"Effect_Huge", false);
		break;
	case One_Effect::BOMB:
		p_Render->Set_Animation(L"Effect_Bomb.bmp", L"Effect_Bomb", 0, 26, Ani_Time, false);
		p_Render->Change_Animation(L"Effect_Bomb", false);
		break;
	case One_Effect::BULLET:
		p_Render->Set_Animation(L"Effect_Bullet.bmp", L"Effect_Bullet", 0, 4, .1f, true);
		p_Render->Change_Animation(L"Effect_Bullet", false);
		break;
	default:
		break;
	}

	p_Render->Pivot(_Pos - Positionf{ .0f, p_Render->size().PartY() });
	p_Render->Set_TransColor(RGB(0, 248, 0));
}

void One_Effect::Update()
{
	if (false == p_Render->IsActing())
	{
		Death(true);
	}
}

