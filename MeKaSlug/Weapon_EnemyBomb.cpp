#include "stdafx.h"
#include "Weapon_EnemyBomb.h"
#include "One_Effect.h"

#include "Collider.h"
#include "Animator.h"
#include "PlayerMgr.h"

#include "ResourceManager.h"


Weapon_EnemyBomb::Weapon_EnemyBomb()
{
	m_v_Gravity = 3.0f;
	m_v_Jump_Force = 600.0f;
	m_Run_Speed = 100;
}


Weapon_EnemyBomb::~Weapon_EnemyBomb()
{
}


void Weapon_EnemyBomb::DebugUpdate()
{
}


void Weapon_EnemyBomb::Start(Positionf _Pos, Dirf _Pos_Dir)
{
	Name(L"E_Explosion");
	m_Pos = _Pos;
	m_pos_Dir = _Pos_Dir;
	m_v_EriPower = 350.0f;


	m_Status_Weapon = Weapon_Type::Explosion;
	Init_Collision();
	Init_Render();

	Update_Force(m_v_Jump_Force);
}

void Weapon_EnemyBomb::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
	{
		return;
	}

	p_Render = Create_Renderer<Animator>(10);
	p_Render->Set_Animation(L"Bomb_Cannon_Bullet.bmp", L"R_Effect", 0, 16, .04f, true);
	p_Render->Set_Animation(L"Bomb_Cannon_Bullet.bmp", L"L_Effect", 16, 0, .04f, true);
	p_Render->Pivot(p_Render->size() * .25f);
	p_Render->Set_TransColor(RGB(255, 105, 0));

	if (.0f < m_pos_Dir.X)
	{
		p_Render->Change_Animation(L"R_Effect");
	}
	if (.0f >= m_pos_Dir.X)
	{
		p_Render->Change_Animation(L"L_Effect");
	}
}

void Weapon_EnemyBomb::Activate()
{
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::SMALL, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}

void Weapon_EnemyBomb::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 30, 30 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	p_Collider->Calculate_Figure_Pos();
	p_Collider->Pivot(p_Collider->size() * .5f);
}

/***************** Update *****************/

void Weapon_EnemyBomb::Update()
{
	UpdateCheckLive();
	Update_Fire();

	// 위치 차를 이용한 벡터 출력
	m_PrevPos = m_Pos;
}

void Weapon_EnemyBomb::Update_Fire()
{
	TheOne::Update_Gravity();
	m_Pos.X += (m_Run_Speed) * DELTATIME * m_pos_Dir.X;
}

void Weapon_EnemyBomb::Update_BottomLine()
{
	if (true == m_b_BottomCheck)
	{
		Activate();
	}
}