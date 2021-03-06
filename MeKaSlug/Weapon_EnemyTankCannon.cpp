#include "stdafx.h"
#include "Weapon_EnemyTankCannon.h"
#include "One_Effect.h"

#include "Collider.h"
#include "Animator.h"
#include "PlayerMgr.h"

#include "ResourceManager.h"



Weapon_EnemyTankCannon::Weapon_EnemyTankCannon()
{
	m_Run_Speed = 300;
}


Weapon_EnemyTankCannon::~Weapon_EnemyTankCannon()
{
}


void Weapon_EnemyTankCannon::Start(Positionf _Pos, Dirf _Pos_Dir)
{
	Name(L"E_Explosion");
	m_Pos = _Pos;
	m_pos_Dir = _Pos_Dir;

	m_Status_Weapon = Weapon_Type::Explosion;
	Init_Collision();
	Init_Render();

	Update_Force(m_v_Jump_Force);
}

void Weapon_EnemyTankCannon::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
	{
		return;
	}

	p_Render = Create_Renderer<Animator>(10);
	p_Render->Set_Animation(L"Tank_Bullet.bmp", L"Bullet", 0, 11, .1f, true);
	p_Render->Pivot(p_Render->size() * .25f);
	p_Render->Set_TransColor(ORANGE);
	p_Render->Change_Animation(L"Bullet");
}

void Weapon_EnemyTankCannon::Activate()
{
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::MIDDLE, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}

void Weapon_EnemyTankCannon::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 50, 50 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Calculate_Figure_Pos();
	p_Collider->Pivot(p_Collider->size() * .5f);
}

/***************** Update *****************/

void Weapon_EnemyTankCannon::Update()
{
	UpdateCheckLive();
	Update_Fire();

	// 위치 차를 이용한 벡터 출력
	m_PrevPos = m_Pos;
}

void Weapon_EnemyTankCannon::Update_Fire()
{
	m_Pos.X += (m_Run_Speed)* DELTATIME * m_pos_Dir.X;
}