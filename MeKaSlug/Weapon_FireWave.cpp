#include "stdafx.h"
#include "Weapon_FireWave.h"
#include "One_Effect.h"

#include "Collider.h"
#include "Animator.h"
#include "PlayerMgr.h"
#include "BossMgr.h"

#include "ResourceManager.h"


Weapon_FireWave::Weapon_FireWave()
{
}


Weapon_FireWave::~Weapon_FireWave()
{
}


void Weapon_FireWave::Start(const Positionf& _Pos)
{
	m_LiveTime = 8.0f;
	m_Run_Speed = 300.0f;
	Name(L"E_Fire");
	m_Pos = _Pos;


	m_Status_Weapon = Weapon_Type::Explosion;
	Init_Collision();
	Init_Render();
}

void Weapon_FireWave::Init_Render()
{
	// 절대 값이 1보다 크면 - 범위 밖이란 듯 - 종료
	if (1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.X) ||
		1.0f < MATHMANAGER.Absolute_Num(m_pos_Dir.Y))
	{
		return;
	}

	p_Render = Create_Renderer<Animator>(30);
	p_Render->Set_Animation(L"Wave_Effect.bmp", L"Down", 0, 11, .04f, true);
	p_Render->Change_Animation(L"Down");

	p_Render->Pivot(p_Render->size() * .25f);
	p_Render->Set_TransColor(ORANGE);
}

void Weapon_FireWave::Activate()
{
	One_Effect* Effect = m_MotherOfTheOne->StateOfOne_Create<One_Effect>();
	Effect->Start(One_Effect::Effect_Type::BIG, m_Pos + Positionf{ .0f, p_Collider->size().PartY() });

	// 다 튀었으면 빨리 사라져야함
	m_LiveTime = .0f;
}

void Weapon_FireWave::Init_Collision()
{
	p_Collider = Create_Collider(L"Weapon", { 200, 100 });
	p_Collider->type(Collider::TYPE::CIRCLE);

	p_Collider->MotherOfTheOne_DE(this);
	//p_Collider->Calculate_Figure_Pos();
	p_Collider->Pivot({ 200, 50 });
}

/***************** Update *****************/

void Weapon_FireWave::Update()
{
	if (true == BossMgr::MainBoss()->BossDie()) { Activate(); }
	m_Pos.X += m_Run_Speed * DELTATIME;
	UpdateCheckLive();
}

