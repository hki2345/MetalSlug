#include "stdafx.h"
#include "Weapon_MedicineCannon.h"

#include "One_Effect.h"

#include "Collider.h"
#include "Animator.h"
#include "PlayerMgr.h"
#include "BossMgr.h"

#include "ResourceManager.h"


Weapon_MedicineCannon::Weapon_MedicineCannon()
{
}


Weapon_MedicineCannon::~Weapon_MedicineCannon()
{
}

void Weapon_MedicineCannon::Start(const Positionf& _Pos)
{
	m_this_Status = MedicineCannonStatus::M_CREATE;
	m_LiveTime = 6.0f;
	m_RotateTime = 5.0f;
	Name(L"E_Explosion");
	m_TargetPos = _Pos;
	m_Pos = m_TargetPos + Positionf{ 200.0f, 50.0f };
	Right = false;


	m_Status_Weapon = Weapon_Type::Explosion;
	Init_Collision();
	Init_Render();
}

void Weapon_MedicineCannon::Update()
{
	UpdateCheckLive();
	if (true == BossMgr::MainBoss()->BossDie()) { Activate(); }
	switch (m_this_Status)
	{
	case Weapon_MedicineCannon::M_CREATE:
		Update_Create();
		break;
	case Weapon_MedicineCannon::M_ROTATE:
		Update_Rotate();
		break;
	case Weapon_MedicineCannon::M_LAUNCH:
		Update_Launch();
		break;
	default:
		break;
	}
}


void Weapon_MedicineCannon::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
	{
		return;
	}

	p_Render = Create_Renderer<Animator>(9);
	p_Render2 = Create_Renderer<Animator>(7);

	p_Render->Set_Animation(L"MedicineCannon.bmp", L"Create", 0, 12, .04f, true);
	p_Render->Set_Animation(L"MedicineCannon.bmp", L"Rotate", 13, 28, .04f, true);
	p_Render->Set_Animation(L"MedicineCannon.bmp", L"None", 29, 29, .04f, true);
	p_Render2->Set_Animation(L"MedicineCannon.bmp", L"Rotate", 13, 28, .04f, true);
	p_Render2->Set_Animation(L"MedicineCannon.bmp", L"None", 29, 29, .04f, true);

	p_Render->Pivot(p_Render->size() * .25f);
	p_Render->Set_TransColor(ORANGE);

	p_Render2->Pivot(p_Render->size() * .25f);
	p_Render2->Set_TransColor(ORANGE);
}

void Weapon_MedicineCannon::Activate()
{
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::MIDDLE, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}

void Weapon_MedicineCannon::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 30, 30 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Pivot(p_Collider->size() * .5f);
}

void Weapon_MedicineCannon::Update_Create()
{
	p_Render->Change_Animation(L"Create");
	p_Render2->Change_Animation(L"None");

	if (false == p_Render->IsActing())
	{
		m_this_Status = M_ROTATE;
		m_ActingTime = .0f;
	}
}

void Weapon_MedicineCannon::Update_Rotate()
{
	m_ActingTime += DELTATIME;

	float Space = 600;

	if (true == Right)
	{
		p_Render->Change_Animation(L"None");
		p_Render2->Change_Animation(L"Rotate");

		// 우로갈때 중심 전
		if (m_TargetPos.X > m_Pos.X && m_TargetPos.X - Space < m_Pos.X)
		{
			m_Pos.X += MATHMANAGER.Absolute_Num(m_TargetPos.X - Space - m_Pos.X) * 1.0f * DELTATIME;
			m_Pos.Y -= 20 * DELTATIME;
		}
		else if (m_TargetPos.X + Space < m_Pos.X + Space * .4f)
		{
			Right = false;
		}
		// 우로갈때 중심 후
		else if (m_TargetPos.X < m_Pos.X && m_TargetPos.X + Space > m_Pos.X)
		{
			m_Pos.X += MATHMANAGER.Absolute_Num(m_TargetPos.X + Space - m_Pos.X) * 1.0f * DELTATIME;
			m_Pos.Y += 20 * DELTATIME;
		}
	}
	else if (false == Right)
	{
		p_Render->Change_Animation(L"Rotate");
		p_Render2->Change_Animation(L"None");

		if (m_TargetPos.X < m_Pos.X && m_TargetPos.X + Space > m_Pos.X)
		{
			m_Pos.X -= MATHMANAGER.Absolute_Num(m_TargetPos.X + Space - m_Pos.X) * 1.0f * DELTATIME;
			m_Pos.Y += 20 * DELTATIME;
		}
		else if (m_TargetPos.X - Space > m_Pos.X - Space * .4f)
		{
			Right = true;
		}
		else if (m_TargetPos.X > m_Pos.X && m_TargetPos.X - Space < m_Pos.X)
		{
			m_Pos.X -= MATHMANAGER.Absolute_Num(m_TargetPos.X - Space - m_Pos.X) * 1.0f * DELTATIME;
			m_Pos.Y -= 20 * DELTATIME;
		}
	}

	if (m_ActingTime > m_RotateTime)
	{
		m_ActingTime = .0f;
		m_this_Status = M_LAUNCH;
		m_TargetPos = PlayerMgr::MainPlayer()->pos();
	}
}

void Weapon_MedicineCannon::Update_Launch()
{
	UpdateCheckLive();
	p_Render->Change_Animation(L"Rotate");

	if (m_Pos.X > m_TargetPos.X)
	{
		m_Pos.X -= 300.0f * DELTATIME;
	}
	else if (m_Pos.X <= m_TargetPos.X)
	{
		m_Pos.X += 300.0f * DELTATIME;
	}

	if (m_Pos.Y > m_TargetPos.Y)
	{
		m_Pos.Y -= 200.0f * DELTATIME;
	}
	else if (m_Pos.Y <= m_TargetPos.Y)
	{
		m_Pos.Y += 200.0f * DELTATIME;
	}
}