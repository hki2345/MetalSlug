#include "stdafx.h"
#include "Weapon_EnemySaruBead.h"
#include "One_Effect.h"

#include "Collider.h"
#include "Animator.h"
#include "PlayerMgr.h"

#include "ResourceManager.h"


Weapon_EnemySaruBead::Weapon_EnemySaruBead()
{
	m_v_Gravity = 3.0f;
	m_Run_Speed = 80;
}


Weapon_EnemySaruBead::~Weapon_EnemySaruBead()
{
}


void Weapon_EnemySaruBead::Start(Positionf _Pos, Dirf _Pos_Dir)
{
	m_LiveTime = 5.0f;
	m_Move = false;
	Name(L"E_Explosion");
	m_Pos = _Pos;
	m_pos_Dir = _Pos_Dir;
	m_v_EriPower = 350.0f;


	m_Status_Weapon = Weapon_Type::Explosion;
	Init_Collision();
	Init_Render();

	Update_Force(m_v_Jump_Force);
}

void Weapon_EnemySaruBead::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
	{
		return;
	}

	p_Render = Create_Renderer<Animator>(10);
	p_Render->Set_Animation(L"Sarubia_Bullet.bmp", L"Down", 0, 8, .04f, true);
	p_Render->Set_Animation(L"Sarubia_Bullet.bmp", L"Stand", 9, 14, .04f, false);
	p_Render->Set_Animation(L"Sarubia_Bullet.bmp", L"Roll", 15, 34, .04f, true);
	p_Render->Change_Animation(L"Down");

	p_Render->Pivot(p_Render->size() * .25f);
	p_Render->Set_TransColor(RGB(255, 105, 0));
}

void Weapon_EnemySaruBead::Activate()
{
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::MIDDLE, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}

void Weapon_EnemySaruBead::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 30, 30 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Calculate_Figure_Pos();
	p_Collider->Pivot(p_Collider->size() * .5f);
}

/***************** Update *****************/

void Weapon_EnemySaruBead::Update()
{
	UpdateCheckLive();
	Update_Fire();

	// 위치 차를 이용한 벡터 출력
	m_PrevPos = m_Pos;
}

void Weapon_EnemySaruBead::Update_Fire()
{
	TheOne::Update_Gravity();

	if (true == m_Move)
	{
		p_Render->Change_Animation(L"Roll");
		m_Pos.X += (m_Run_Speed)* DELTATIME * m_pos_Dir.X;
	}
	else if (Obj_Stand == m_Status_Obj)
	{
		p_Render->Change_Animation(L"Stand");
		m_Move = true;
	}
}

